from pathlib import Path
from pprint import pprint
import logging
import os
import subprocess

log = logging.getLogger()
logging.basicConfig(level=logging.INFO)

CMAKE_LIST_TXT = 'CMakeLists.txt'
BUILD_DIR = 'build'

CMAKE_LIST_TEMPLATE = """\
project(main)

add_executable(main main.cpp)
"""


def FindAllProjects(root_dir):
    root_dir = Path(root_dir)
    main_files = root_dir.glob('**/*.cpp')
    # pprint(list(main_files))
    return list(main_files)


def CreateAndBuildProject(main_file):
    main_file = Path(main_file)
    log.info(f'########## Doing {main_file} ########')

    cmake_lists = main_file.with_name(CMAKE_LIST_TXT)
    cmake_lists.write_text(CMAKE_LIST_TEMPLATE)
    build_dir = main_file.with_name(BUILD_DIR).absolute()
    build_dir.mkdir(exist_ok=1)
    build_dir = build_dir.absolute()
    source_dir = main_file.parent.absolute()

    os.system(f'cmake -G Ninja -B "{build_dir}" -S "{source_dir}" ')
    os.system(f'cmake --build "{build_dir}" ')


ROOT_DIR = '/home/cgsdfc/code'

main_files = FindAllProjects(ROOT_DIR)
for f in main_files:
    CreateAndBuildProject(f)
