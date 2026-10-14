# C3C Version Requirements

This project uses C3C 0.8.5_1 to compile the C3 source code into a static library (librun.a), which is then linked with the Bouffalo SDK to build the final firmware.

Make sure you have C3C 0.8.5_1 installed and properly configured before building the project.

# ai_m61_32s_template

You don't need to specify the CHIP and BOARD parameters when building for the AI-Thinker M61-32S, as the default configuration is already supported.

Run make to compile the C3 source code, generate the static library (librun.a), link it with the Bouffalo SDK, and build the final firmware.

By default, the generated firmware targets BL616/BL618-compatible configurations.

To flash the firmware to your board, run:

make flash COMX=xxx

Replace xxx with your board's serial port name.

## Support CHIP

| CHIP              | Remark |
|:-----------------:|:------:|
| BL602/BL604       |        |
| BL702/BL704/BL706 |        |
| BL702L/BL704L     |        |
| BL616/BL618       |        |
| BL618DG           |        |


## Compile

- BL602/BL604

```
make CHIP=bl602 BOARD=bl602dk
```

- BL702/BL704/BL706

```
make CHIP=bl702 BOARD=bl702dk
```

- BL702L/BL704L

```
make CHIP=bl702l BOARD=bl702ldk
```

- BL616/BL618

```
make CHIP=bl616 BOARD=bl616dk
```

- BL618DG

```
make CHIP=bl618dg BOARD=bl618dgdk CPU_ID=ap
make CHIP=bl618dg BOARD=bl618dgdk CPU_ID=np
```

## Flash

```
make flash CHIP=chip_name COMX=xxx # xxx is your com name
```
