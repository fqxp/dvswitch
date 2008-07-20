add_definitions(${GTKMM_CFLAGS_OTHER} ${LIBAVCODEC_CFLAGS_OTHER})
include_directories(${GTKMM_INCLUDE_DIRS} ${LIBAVCODEC_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS} ${LIBAVCODEC_LIBRARY_DIRS})

add_definitions(-DSHAREDIR="\\"${sharedir}\\"")

set(common_sources config.c dif.c socket.c)

add_executable(dvsink-command dvsink-command.c ${common_sources})

add_executable(dvsink-files dvsink-files.c ${common_sources})

add_executable(dvsource-file dvsource-file.c frame_timer.c ${common_sources})
target_link_libraries(dvsource-file pthread rt)

add_executable(dvsource-firewire dvsource-firewire.c ${common_sources})

add_executable(dvswitch dvswitch.cpp mixer.cpp frame_timer.c
  mixer_window.cpp dv_display_widget.cpp dv_selector_widget.cpp
  server.cpp auto_pipe.cpp os_error.cpp video_effect.c frame_pool.cpp
  frame.c auto_codec.cpp ${common_sources})
target_link_libraries(dvswitch boost_thread pthread rt Xv
  ${GTKMM_LIBRARIES} ${LIBAVCODEC_LIBRARIES})

install(TARGETS dvsink-command dvsink-files dvsource-file dvsource-firewire
                dvswitch
        DESTINATION ${bindir})