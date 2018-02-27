TEMPLATE = subdirs

SUBDIRS += core test-round-2018 hashcode-2017
test-round-2018.depends = core
hashcode-2017.depends = core
