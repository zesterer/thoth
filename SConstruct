# Set up project information

project_info = dict()

project_info["name"] = "thoth"

project_info["version_major"] = 0
project_info["version_minor"] = 0
project_info["version_release"] = 1
project_info["release_name"] = "puffin"

project_info["target"] = "x86_64"

# Enter the necessary subdirectories

subdirs = []

subdirs += ["include/SConscript"]
subdirs += ["kernel/SConscript"]
subdirs += ["apps/SConscript"]

SConscript(subdirs, exports = ["project_info"])
