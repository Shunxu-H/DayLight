

message(${SOURCE_DIR}/resources )
message( ${DESTINATION_DIR})
file( COPY ${SOURCE_DIR}/resources/GLSL ${SOURCE_DIR}/resources/data  DESTINATION ${DESTINATION_DIR} )