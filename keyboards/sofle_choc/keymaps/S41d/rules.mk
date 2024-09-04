ENCODER_MAP_ENABLE = yes
EXTRAKEY_ENABLE = yes 
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
WPM_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes

# Reduce compiled size
LTO_ENABLE = yes
TAP_DANCE_ENABLE = no
MOUSEKEY_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
COMMAND_ENABLE = no
CONSOLE_ENABLE = no
MUSIC_ENABLE = no
MAGIC_ENABLE = no

SRC += doggo.c spaceship.c