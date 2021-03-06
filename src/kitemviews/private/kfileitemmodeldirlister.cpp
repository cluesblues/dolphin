/*
 * SPDX-FileCopyrightText: 2006-2012 Peter Penz <peter.penz19@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "kfileitemmodeldirlister.h"

#include <KLocalizedString>
#include <KIO/Job>

KFileItemModelDirLister::KFileItemModelDirLister(QObject* parent) :
    KDirLister(parent)
{
    setAutoErrorHandlingEnabled(false, nullptr);
}

KFileItemModelDirLister::~KFileItemModelDirLister()
{
}

void KFileItemModelDirLister::handleError(KIO::Job* job)
{
    if (job->error() == KIO::ERR_IS_FILE) {
        Q_EMIT urlIsFileError(url());
    } else {
        const QString errorString = job->errorString();
        if (errorString.isEmpty()) {
            Q_EMIT errorMessage(i18nc("@info:status", "Unknown error."));
        } else {
            Q_EMIT errorMessage(errorString);
        }
    }
}

