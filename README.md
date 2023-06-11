<h1 align="center">IRIS</h1>

![splash](assets/splash.png)

> Project currently work in progress

# Rationale

- Create a tool for close friends and I to communicate securely over insecure channels.
- Easily spin out wallet software for another project I've been working on where most of the ECC logic comes from: https://github.com/ramity/ramium
- Explore compiling c++ executables for multiple platforms

# Planned design

- Designed for self-contained, USB-flashdrive environments in airgapped environments

# Planned features

- Dockerized development and build environments
- Portable 64-bit Window and 64-bit Linux binary executables

## Key formats
- ECC

## Key management
- Generation
- Distribution
- Storage
- Destruction

## Key operations
- Encryption
- Decryption
- Signing
- Verification

---

## Setting up dev environment
(Host computer)
```
docker compose up -d
# Enter container
docker exec -it iris_dev bash
```

## Compile cryptopp for both linux and windows platforms

(Inside container)
```
./scripts/lib/compile-all-cryptopp.sh
```

## Run linux tests

(Inside container)
```
./scripts/test.sh
```

## Compile ecc test for windows environment

(Inside container)
```
./scripts/w64-compile-ecc.sh
```

(Host computer - assuming windows environment)
```
./bin/win64-cc-test.exe
```

## Building, downloadable releases, update utilities, and more planned...
