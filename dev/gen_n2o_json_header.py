import json
import zlib
from pathlib import Path

root = Path(__file__).resolve().parents[1]
src = root / "dev" / "fluids" / "NitrousOxide.json"
dst = root / "include" / "NitrousOxide_JSON.h"

raw = json.loads(src.read_text(encoding="utf-8"))
info = raw.get("INFO", {})
raw["INFO"] = {k: info[k] for k in ("NAME", "CAS", "ALIASES", "MOLAR_MASS", "REFPROP_NAME") if k in info}
# Classical ANCILLARIES are enough for PQ saturation; drop Chebyshev SUPERANCILLARY
# tables to fit the STM32H723 1MB flash budget.
for eos in raw.get("EOS", []):
    if isinstance(eos, dict):
        # Keep BibTeX_* keys (loader requires them via cpjson::get_string).
        eos.pop("SUPERANCILLARY", None)
text = json.dumps(raw, separators=(",", ":")).encode("utf-8")
data = zlib.compress(text, 9)

lines = [
    "#pragma once",
    "// Auto-generated zlib-compressed N2O-only fluid payload.",
    "// Source: dev/fluids/NitrousOxide.json (minified then zlib level 9).",
    "// Regenerate with: python dev/gen_n2o_json_header.py",
    f"static const unsigned NitrousOxide_JSON_raw_len = {len(text)};",
    f"static const unsigned NitrousOxide_JSON_z_len = {len(data)};",
    "static const unsigned char NitrousOxide_JSON_z[] = {",
]
chunk = []
for b in data:
    chunk.append(f"0x{b:02x}")
    if len(chunk) == 16:
        lines.append("    " + ", ".join(chunk) + ",")
        chunk = []
if chunk:
    lines.append("    " + ", ".join(chunk) + ",")
lines.append("};")
lines.append("")
dst.write_text("\n".join(lines), encoding="utf-8")
print(f"Wrote {dst} ({dst.stat().st_size} bytes); raw={len(text)} zlib={len(data)}")
