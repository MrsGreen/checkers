bin_PROGRAMS=serverexe clientexe
serverexe_SOURCES=server.c server/inc/server.h inc/global.h
clientexe_SOURCES=client.c client/inc/client.h inc/global.h
SUBDIRS=lib server/lib client/lib
LDADD = lib/libvar.a server/lib/libinit.a server/lib/libcheck_msg.a server/lib/libmake_move.a server/lib/libsdata.a server/lib/libkill_list.a client/lib/libscreen.a client/lib/libcdata.a
