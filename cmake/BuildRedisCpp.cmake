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

# build reids-plus-plus
# maybe be used by dynamic lib
set(REDIS_PLUS_PLUS_BUILD_TEST OFF CACHE BOOL "Build tests.")
#set(REDIS_PLUS_PLUS_BUILD_SHARED OFF CACHE BOOL " Only build a static library.")
add_subdirectory_static(thirdparty/redis-plus-plus EXCLUDE_FROM_ALL)
set(REDIS_PLUS_PLUS_LIBRARIES redis++)
set(REDIS_PLUS_PLUS_INCLUDE_DIR thirdparty/redis-plus-plus/src/sw)