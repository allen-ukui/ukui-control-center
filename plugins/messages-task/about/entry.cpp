/*
    SPDX-FileCopyrightText: 2012-2020 Harald Sitter <sitter@kde.org>
    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#include "entry.h"

Entry::Entry(const KLocalizedString &label_, const QString &value_)
    : label(label_)
    , value(value_)
{
    Q_ASSERT(label.isEmpty() || localizedLabel(Language::English).endsWith(':'));
}

Entry::~Entry() = default;

// When false this entry is garbage (e.g. incomplete data) and shouldn't be rendered.
bool Entry::isValid() const
{
    return !label.toString().isEmpty() && !value.isEmpty();
}

// Returns textual representation of entry.
QString Entry::diagnosticLine(Language language) const
{
    // FIXME: This isn't really working for right-to-left
    // The answer probably is in uncide control characters, but
    // didn't work when tried.
    // Essentially what needs to happen is that the label should be RTL
    // that is to say the colon should be on the left, BUT englishy words
    // within that should be LTR, everything besides the label should be LTR
    // because we do not localize the values I don't think?
    return localizedLabel(language) + ' ' + value + '\n';
}

QString Entry::localizedLabel(Language language) const
{
    switch (language) {
    case Language::System:
        return label.toString();
    case Language::English:
        // https://bugs.kde.org/show_bug.cgi?id=416247
        return label.toString(QStringList { QStringLiteral("en_US") });
    }
    Q_UNREACHABLE();
    return QStringLiteral("Unknown Label Language %1 (bug in KInfocenter!):").arg(
                QString::number(static_cast<int>(language)));
}
