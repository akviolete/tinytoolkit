#
# 项目名
#
SET(PROGRAM_NAME tinyToolkit-extra)


#
# 定义当前目录下源文件分组
#
IF(WIN32 OR APPLE)

	#
	# 遍历递归当前目录定义源文件分组
	#
	RECURSE_CURRENT_DIRECTORY_SOURCE_FILE_GROUP()

ENDIF()


#
# 库文件的生成目录
#
IF(WIN32)

	#
	# 设置库文件生成目录
	#
	SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

ELSE()

	#
	# 设置库文件生成目录
	#
	SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

ENDIF()


#
# 遍历递归当前目录获取源文件
#
RECURSE_CURRENT_DIRECTORY_SOURCE_FILE(SOURCE_FILES)


#
# 链接源文件, 生成库文件
#
ADD_LIBRARY(${PROGRAM_NAME} SHARED ${SOURCE_FILES})


#
# 根据项目名链接多个动态库
#
TRAVERSE_LIBRARY_FOR_PROGRAM_NAME(
		ssl
		curl
		crypto
		sqlite3
		memcached)


#
# 安装库文件
#
INSTALL(TARGETS tinyToolkit-extra
		LIBRARY DESTINATION ${LIBRARY_INSTALL_PREFIX}
		ARCHIVE DESTINATION ${LIBRARY_INSTALL_PREFIX})


#
# 遍历递归指定目录安装头文件
#
TRAVERSE_INSTALL_INCLUDE(curl						${INCLUDE_INSTALL_PREFIX}/curl)
TRAVERSE_INSTALL_INCLUDE(sqlite						${INCLUDE_INSTALL_PREFIX}/sqlite)
TRAVERSE_INSTALL_INCLUDE(openssl					${INCLUDE_INSTALL_PREFIX}/openssl)
TRAVERSE_INSTALL_INCLUDE(memcached					${INCLUDE_INSTALL_PREFIX}/memcached)
TRAVERSE_INSTALL_INCLUDE(${CMAKE_CURRENT_LIST_DIR}	${INCLUDE_INSTALL_PREFIX})

