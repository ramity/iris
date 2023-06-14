<h1 align="center">IRIS</h1>

![splash](assets/splash.png)

> Project currently work in progress

# ToC

- [Quick start](#quick-start)
- [Commands](#commands)
- [Example usage](#example-usage)
- [Rationale](#rationale)
- [Planned design](#planned-design)
- [Planned features](#planned-features)
- [Key formats](#key-formats)
- [Key management](#key-management)
- [Key operations](#key-operations)
- [Setting up dev environment](#setting-up-dev-environment)
- [Compile cryptopp for both linux and windows](#compile-cryptopp-for-both-linux-and-windows)
- [Compile iris for both linux and windows](#compile-iris-for-both-linux-and-windows)
- [Run linux tests](#run-linux-tests)
- [A note on deterministic keys](#a-note-on-deterministic-keys)

# Quick start

- Download and unzip latest release ([Linux](https://github.com/ramity/iris/releases/download/v0.1.0/linux-64.zip), [Windows](https://github.com/ramity/iris/releases/download/v0.1.0/windows-64.zip))
- Execute compiled binary from CLI

# Commands

```
iris --help
iris keypair --help
iris keypair generate [args]
iris keypair delete [args]
iris keypair encrypt [args]
iris keypair decrypt [args]
iris keypair sign [args]
iris identity --help
iris identity add [args]
iris identity remove [args]
iris identity list [args]
iris identity verify [args]
```

# Example usage

### Alice and Bob wish to communicate over an unsecure channel. The below details a user story featuring keypair generation and public key sharing using linux devices. The same can be accomplished on windows devices with variances (`./iris`->`iris.exe`, `cat`->`type`, etc).

---

Alice generates a keypair:
```
./iris keypair generate ./keys/private_key ./keys/public_key
```

Bob generates a keypair:
```
./iris keypair generate ./keys/private_key ./keys/public_key
```

Alice `cat`s her public key to the console, copies it, and shares it to Bob over an unsecure channel:

```
cat ./keys/public_key
```
> MIGbMBAGByqGSM49AgEGBSuBBAAjA4GGAAQBW9w/ObxNLQjObQ8XUVKF9kgk7NVlA+5SjItlL5ZuW1KR5GHForrGz244Xp1LG1/higCPCTD5DnjeIwX8EDNQunsBGOuR9BX1ldKdMJuOl9KufRRKuIFFOK4ihMum4sfHFV18BKxhlJkrqay6hqLnUvsRx/C32X7j70vLHxeRXhGAE4g=

Bob adds Alice's public key to his iris instance:

```
./iris identity add ./identities/alice --public_key=MIGbMBAGByqGSM49AgEGBSuBBAAjA4GGAAQBW9w/ObxNLQjObQ8XUVKF9kgk7NVlA+5SjItlL5ZuW1KR5GHForrGz244Xp1LG1/higCPCTD5DnjeIwX8EDNQunsBGOuR9BX1ldKdMJuOl9KufRRKuIFFOK4ihMum4sfHFV18BKxhlJkrqay6hqLnUvsRx/C32X7j70vLHxeRXhGAE4g=
```

> File written successfully

Bob `cat`s his public key to the console, copies it, and shares it to Alice over an unsecure channel:

```
cat ./keys/public_key
```

> MIGbMBAGByqGSM49AgEGBSuBBAAjA4GGAAQBUXSK3fQJoz460Rwb/l/opXIJI6Spa/nRYwYjnQbDqknGOexgjbxr+pivGkIH2VO41ONU+aDCMcJ+QM4t+NBrrpsAr4ewQFgNmk1kBa11A60sc35SRVfJqAccvF3mAbE+t8WAkBnioRA/xo3VngZPQyDs6NuNgJxQqIEzpCyYC9bVQVs=

Alice adds Bob's public key to her iris instance:

```
./iris identity add ./identities/alice --public_key=MIGbMBAGByqGSM49AgEGBSuBBAAjA4GGAAQBUXSK3fQJoz460Rwb/l/opXIJI6Spa/nRYwYjnQbDqknGOexgjbxr+pivGkIH2VO41ONU+aDCMcJ+QM4t+NBrrpsAr4ewQFgNmk1kBa11A60sc35SRVfJqAccvF3mAbE+t8WAkBnioRA/xo3VngZPQyDs6NuNgJxQqIEzpCyYC9bVQVs
```

> File written successfully

Alice and Bob can now utilize the saved identities to encrypt text, share ciphertexts, verify sign messages, etc.

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

## Compile cryptopp for both linux and windows

(Inside container)
```
./scripts/lib/compile-all-cryptopp.sh
```

## Compile iris for both linux and windows

(Inside container)
```
./scripts/build.sh
```

## Run linux tests

(Inside container)
```
./scripts/test.sh
```

## A note on deterministic keys

Iris supports the use of a master seed that is akin to a [deterministic wallet](https://en.bitcoin.it/wiki/Deterministic_wallet). The master seed serves as the root from which all subsequent keypairs are derived. The generation process is deterministic, meaning that given the same master seed, iris will always produce the same sequence of keypairs. This property is crucial for keypair backup and recovery, as it allows users to regenerate their entire keypair sequence by simply knowing and inputting the master seed.

The use of a master seed does introduce a potential security risk. If an attacker gains access to the master seed, they can regenerate all the keypairs.

```
./iris keypair generate ./keys/private_key ./keys/public_key toUseEvenGoWantToDoLookMoreLike 42
```

> The `keypair generate` command generating the 42th derived key from the "toUseEvenGoWantToDoLookMoreLike" master seed.

In iris, deterministic keys are generated by hashing a provided seed string `(n * generation_difficulty)` times. The `generation_difficulty` multiplier is present to slow down attacks against weak user-chosen strings.

After the rounds of hashing, the seed hash is then used by taking the first 32 bytes as a key and the following 16 bytes as an initialization vector to create a unqiue 256 bit AES key. This key is then used to deterministically generate a keypair.
