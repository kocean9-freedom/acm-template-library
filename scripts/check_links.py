#!/usr/bin/env python3
"""检查仓库 Markdown 中的相对链接是否指向现有文件。"""

from pathlib import Path
import re
import sys
from urllib.parse import unquote


root = Path(__file__).resolve().parents[1]
bad = []
pattern = re.compile(r"\[[^]]*\]\(([^)]+)\)")
inline_code = re.compile(r"(`+).*?\1")


def without_code(text: str) -> str:
    """移除围栏和行内代码，避免把 C++ 的 `[](...)` 当成链接。"""
    kept = []
    fence = None
    for line in text.splitlines():
        stripped = line.lstrip()
        if fence is not None:
            if stripped.startswith(fence):
                fence = None
            continue
        if stripped.startswith("```"):
            fence = "```"
            continue
        if stripped.startswith("~~~"):
            fence = "~~~"
            continue
        kept.append(inline_code.sub("", line))
    return "\n".join(kept)

for md in root.rglob("*.md"):
    text = without_code(md.read_text(encoding="utf-8"))
    for target in pattern.findall(text):
        target = target.strip().split("#", 1)[0]
        if not target or "://" in target or target.startswith("mailto:"):
            continue
        path = (md.parent / unquote(target)).resolve()
        if not path.exists():
            bad.append(f"{md.relative_to(root)} -> {target}")

if bad:
    print("broken markdown links:")
    print("\n".join(bad))
    sys.exit(1)

print("markdown links passed")
