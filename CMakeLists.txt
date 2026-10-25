idf_build_get_property(idf_target IDF_TARGET)
if("${idf_target}" STREQUAL "esp32p4")
list(APPEND extra_requires esp-hosted-tanmatsu)
endif()

idf_component_register(
	SRCS
		radio_ir_protocol_client.c
	INCLUDE_DIRS
		"include"
	PRIV_REQUIRES
		${extra_requires}
)
