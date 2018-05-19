# CEdit

A text editor written completely in C.

## Status [![Build Status](https://travis-ci.org/sambhav2612/textC.svg?branch=master)](https://travis-ci.org/sambhav2612/textC) [ ![Codeship Status for sambhav2612/textC](https://app.codeship.com/projects/dd04a380-f7c1-0135-594b-7af7195f2991/status?branch=master)](https://app.codeship.com/projects/277969)

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

## Machine setup instructions

Refer: https://viewsourcecode.org/snaptoken/kilo/01.setup.html

## Contribution Guideline

Contributions are welcome. Do check the existing contribution guideline [here](https://github.com/sambhav2612/CEdit/blob/master/.github/CONTRIBUTING.md).

## License

![GPL-3.0](http://200billionscandal.typepad.com/.a/6a00d83451da3169e20147e36f3e4a970b-800wi)
