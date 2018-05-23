# CEdit

A text editor written completely in C.

## Status [![Build Status](https://travis-ci.org/sambhav2612/CEdit.svg?branch=master)](https://travis-ci.org/sambhav2612/CEdit)

At version 0.0.10 and compiling without warning(s).

## Latest Update

Add filetype detection and syntax highlighting for C and CPP.

## Upcoming Update

Add unit testing via Check Framework.

## Installation

```bash
# init local repo
$ git init

# add repo remote
$ git remote add upstream https://github.com/sambhav2612/CEdit.git

# clone the repo from remote
$ git clone upstream

# cd into the directory
$ cd CEdit

# install gcc and make
$ npm run install-dependencies

# test for installation of gcc and make
$ npm run test-dependencies

# build executable and run
$ npm run build-executable

# manually run the executable with new file
$ ./editor

# manually run the executable with open file
$ ./editor <FILENAME.EXTENSION>

# to keep up-to-date with remote
$ git pull upstream master


# == OPTIONAL ==
# install packages 
$ npm install

# start a local server with current dir content in JSON format served online
$ npm run start-server
```

## Known Issues

Check the issue tracker for known issues [here](https://github.com/sambhav2612/CEdit/issues/created_by/sambhav2612).

## Machine setup instructions

Refer: https://viewsourcecode.org/snaptoken/kilo/01.setup.html

## Contribution Guideline

Contributions are welcome. Do check the existing contribution guideline [here](https://github.com/sambhav2612/CEdit/blob/master/.github/CONTRIBUTING.md).

## License

© Sambhav Jain 2018 [sambhavjain2612@gmail.com](mailto:sambhavjain2612@gmail.com)

![GPL-3.0](http://200billionscandal.typepad.com/.a/6a00d83451da3169e20147e36f3e4a970b-800wi)
