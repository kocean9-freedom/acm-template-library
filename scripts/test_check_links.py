#!/usr/bin/env python3
"""回归测试：代码示例不能被 Markdown 链接检查器误报。"""

from pathlib import Path
import subprocess
import sys
import unittest


class CheckLinksTest(unittest.TestCase):
    def test_cpp_signatures_inside_code_are_not_links(self):
        checker = Path(__file__).with_name("check_links.py")
        result = subprocess.run(
            [sys.executable, str(checker)],
            capture_output=True,
            text=True,
            check=False,
        )
        self.assertEqual(0, result.returncode, result.stdout + result.stderr)


if __name__ == "__main__":
    unittest.main()
