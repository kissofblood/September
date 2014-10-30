#ifndef QSSKEYWORDS_H
#define QSSKEYWORDS_H

#include <QHash>

namespace KeyWords {

static const QHash<const char*, const char*> widget = {
    { "QAbstractScrollArea",    "QAbstractScrollArea"   },
    { "QCheckBox",              "QCheckBox"             },
    { "QColumnView",            "QColumnView"           },
    { "QComboBox",              "QComboBox"             },
    { "QDateEdit",              "QDateEdit"             },
    { "QDateTimeEdit",          "QDateTimeEdit"         },
    { "QDialog",                "QDialog"               },
    { "QDialogButtonBox",       "QDialogButtonBox"      },
    { "QDockWidget",            "QDockWidget"           },
    { "QDoubleSpinBox",         "QDoubleSpinBox"        },
    { "QFrame",                 "QFrame"                },
    { "QGroupBox",              "QGroupBox"             },
    { "QHeaderView",            "QHeaderView"           },
    { "QLabel",                 "QLabel"                },
    { "QLineEdit",              "QLineEdit"             },
    { "QListView",              "QListView"             },
    { "QListWidget",            "QListWidget"           },
    { "QMainWindow",            "QMainWindow"           },
    { "QMenu",                  "QMenu"                 },
    { "QMenuBar",               "QMenuBar"              },
    { "QMessageBox",            "QMessageBox"           },
    { "QProgressBar",           "QProgressBar"          },
    { "QPushButton",            "QPushButton"           },
    { "QRadioButton",           "QRadioButton"          },
    { "QScrollBar",             "QScrollBar"            },
    { "QSizeGrip",              "QSizeGrip"             },
    { "QSlider",                "QSlider"               },
    { "QSpinBox",               "QSpinBox"              },
    { "QSplitter",              "QSplitter"             },
    { "QStatusBar",             "QStatusBar"            },
    { "QTabBar",                "QTabBar"               },
    { "QTabWidget",             "QTabWidget"            },
    { "QTableView",             "QTableView"            },
    { "QTableWidget",           "QTableWidget"          },
    { "QTextEdit",              "QTextEdit"             },
    { "QTimeEdit",              "QTimeEdit"             },
    { "QToolBar",               "QToolBar"              },
    { "QToolButton",            "QToolButton"           },
    { "QToolBox",               "QToolBox"              },
    { "QToolTip",               "QToolTip"              },
    { "QTreeView",              "QTreeView"             },
    { "QTreeWidget",            "QTreeWidget"           },
    { "QWidget",                "QWidget"               }
};

}

#endif // QSSKEYWORDS_H
