/*
 * File: main.cpp
 * Project: HttpClient
 * File Created: Tuesday, 5th July 2022 2:29:22 PM
 * Author: nknab
 * Email: adverb_rushed_09@icloud.com
 * Version: 1.0
 * Brief: <<brief>>
 * -----
 * Last Modified: Wednesday, 6th July 2022 10:36:34 AM
 * Modified By: nknab
 * -----
 * Copyright ©2022 nknab
 */

#include <QCoreApplication>

#include "hctest.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    return QTest::qExec(new HCTest, argc, argv);
}
