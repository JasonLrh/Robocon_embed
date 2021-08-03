Robocon_Path = Robocon
C_INCLUDES += \
-I$(Robocon_Path)/inc

C_SOURCES += \
$(Robocon_Path)/src/rbc_log.c \
$(Robocon_Path)/src/rbc.c \
$(Robocon_Path)/src/rbc_pwr.c \
$(Robocon_Path)/src/rbc_safe.c 