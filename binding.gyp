{
    "targets": [{
        "target_name": "rfm95",
        "sources": [
          "./src/rfm95js.c",
          "./src/rfm95.c",
          "./src/rfm95spi.c",
          "./src/rfm95spi_dummy.c",
          "./src/rfm95spi_bcm2835.c"
        ],
        'include_dirs': [
          "./inc"
        ],
        "libraries": [
          "/usr/local/lib/libbcm2835.a"
        ]
    }]
}
