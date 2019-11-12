# Synthetic Application

This repository contains a *Synthetic Application* written by Maicon Alves and modified by Luan Teylo.

The current version emulates three computational phases:
  - Memory Access Loop
  - Compute Intensive Loop
  - Write/Read Operation

### Docker Installation
```sh
$ cd synthetic/
$ docker build -t <image-name> .
```

### Execution
```sh
$ docker run --rm  <image-name> <matrix-size>
```