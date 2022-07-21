# Copyright 2020-2021 Alibaba Group Holding Limited.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# build hiredis
set(DISABLE_TESTS ON CACHE BOOL "Build tests.")
#<<<<<<< HEAD
#add_subdirectory_static(thirdparty/hiredis)
#=======
add_subdirectory_static(thirdparty/hiredis EXCLUDE_FROM_ALL)
#>>>>>>> 43eba656b5b93fa9b1840d392b46927ac1ca14a5

target_include_directories(hiredis PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/thirdparty>)
# 这就是在指定find_package()的路径
set(hiredis_DIR "${PROJECT_BINARY_DIR}/thirdparty/hiredis")
set(hiredis_INCLUDEDIR "${PROJECT_SOURCE_DIR}/thirdparty")

set(HIREDIS_INCLUDE_DIR thirdparty/hiredis)
# 因为hiredis是一个target，所以路径是知道的？
set(HIREDIS_LIBRARIES hiredis)
