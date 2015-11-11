![round_logo](../img/round_logo.png)

# Getting Started

Official binary distributions are available for Linux and Mac OS X. If a binary distribution is not available for your combination of operating system and architecture, try installing from source.

## Getting Round

### Linux

#### Docker

To get started with Docker on Linux, run the following in a terminal:

```
docker run cybergarage/round:latest
```

### MacOSX

First, you have to install the following package on MacOSX.

- [Java for OS X 2014-001](http://support.apple.com/kb/DL1572)

#### Homebrew

To get started on MacOSX, run the following in a terminal:

```
brew tap cybergarage/brew
brew install round++
```

### Installing from source

Round is an open source project, distributed under a [BSD-style license](../LICENSE). If you want to  build from source, follow [the source installation instructions](./round_install_from_source.md).

## Running Round

First, start a single node of round:

```
roundd
```

Next, let's start the client utility command:

```
round shell
```

## Next Steps

Let's try the following tour to know functions of Round in more detail.

- [Tour of Round](./round_tour.md)
