set(sources
	src/utils.cpp
	src/message-buffer.cpp
)

set(exe_sources
	src/server.cpp
	${sources}
)

set(headers
	src/message-buffer.hpp
	src/utils.hpp
)

set(test_sources
	src/message_test.cpp
)
