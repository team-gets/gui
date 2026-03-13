#!/usr/bin/env python3

import os
import tarfile
import urllib.request

from os.path import join, abspath

gr = {
    "msvc": "https://gr-framework.org/downloads/gr-latest-Windows-x86_64-msvc.tar.gz"
}

paths = {
    "lib": abspath(join(__file__, "..")),
    "repo_root": abspath(join(__file__, "..", ".."))
}

def attempt_dl(link: str, outf: str|os.PathLike) -> int:
    try:
        print("Requesting download...")
        lib_get = urllib.request.urlretrieve(link, outf)
    except:
        print(f"Failed to download file at {link}")
        return 1
    return 0

if __name__ == "__main__":
    gr_tar = join(paths["lib"], "gr.tar.gz")
    dlstat = attempt_dl(gr["msvc"], gr_tar)
    if (dlstat == 1):
        raise RuntimeError

    print("Extracting binaries from tarball...")
    akaibu = tarfile.open(gr_tar)
    akaibu.extractall(paths["lib"], filter="data")
    akaibu.close()
    print("All done!")
