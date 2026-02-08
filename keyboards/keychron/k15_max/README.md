# Vial support for the K15

Taken from https://github.com/Keychron/qmk_firmware/tree/wireless_playground/keyboards/keychron/k15_max
and added support for Vial.

Build:
```
qmk compile -kb keychron/k15_max/ansi_encoder -km vial -j 11
```

Flash:
```
qmk flash keychron_k15_max_ansi_encoder_vial.bin
```

Reset to bootloader mode for flashing:
Hold down the Esc key or the reset button underneath the right space bar while connecting the USB cable.
