TEMPLATE = subdirs

SUBDIRS += \
    task_b \
    task_d \
    task_e \
    extra

# MPI Settings
QMAKE_CXX = mpicxx
QMAKE_CXX_RELEASE = $$QMAKE_CXX
QMAKE_CXX_DEBUG = $$QMAKE_CXX
QMAKE_LINK = $$QMAKE_CXX
QMAKE_CC = mpicc

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lmpi
