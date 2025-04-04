/* ----------------------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   https://www.lammps.org/, Sandia National Laboratories
   LAMMPS development team: developers@lammps.org

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    outputFormat.setForeground(Qt::darkYellow);
    outputFormat.setFontWeight(QFont::Bold);
    readFormat.setForeground(Qt::magenta);
    readFormat.setFontWeight(QFont::Bold);
    latticeFormat.setForeground(Qt::darkGreen);
    latticeFormat.setFontWeight(QFont::Bold);
    particleFormat.setForeground(Qt::darkRed);
    particleFormat.setFontWeight(QFont::Bold);
    setupFormat.setForeground(Qt::darkCyan);
    setupFormat.setFontWeight(QFont::Bold);
    runFormat.setForeground(Qt::darkBlue);
    runFormat.setFontWeight(QFont::Bold);
    defineFormat.setForeground(Qt::darkMagenta);
    defineFormat.setFontWeight(QFont::Bold);

    numberFormat.setForeground(Qt::blue);
    commentFormat.setForeground(Qt::red);
    stringFormat.setForeground(Qt::darkGreen);
    stringFormat.setFontWeight(QFont::Normal);

    const QString output_keywords[] = {
        QStringLiteral("^\\s*log\\W"),           QStringLiteral("^\\s*write_data\\W"),
        QStringLiteral("^\\s*write_dump\\W"),    QStringLiteral("^\\s*write_coeff\\W"),
        QStringLiteral("^\\s*info\\W"),          QStringLiteral("^\\s*shell\\W"),
        QStringLiteral("^\\s*write_restart\\W"), QStringLiteral("^\\s*restart\\W"),
        QStringLiteral("^\\s*dump\\W"),          QStringLiteral("^\\s*undump\\W"),
        QStringLiteral("^\\s*thermo\\W"),        QStringLiteral("^\\s*thermo_modify\\W"),
        QStringLiteral("^\\s*thermo_style\\W"),  QStringLiteral("^\\s*print\\W"),
        QStringLiteral("^\\s*timer\\W")};
    for (const QString &pattern : output_keywords) {
        rule.pattern = QRegularExpression(pattern);
        rule.format  = outputFormat;
        highlightingRules.append(rule);
    }

    const QString read_keywords[] = {
        QStringLiteral("^\\s*include\\W"), QStringLiteral("^\\s*read_restart\\W"),
        QStringLiteral("^\\s*read_data\\W"), QStringLiteral("^\\s*read_dump\\W"),
        QStringLiteral("^\\s*molecule\\W")};
    for (const QString &pattern : read_keywords) {
        rule.pattern = QRegularExpression(pattern);
        rule.format  = readFormat;
        highlightingRules.append(rule);
    }

    const QString lattice_keywords[] = {
        QStringLiteral("^\\s*boundary\\W"),     QStringLiteral("^\\s*units\\W"),
        QStringLiteral("^\\s*atom_style\\W"),   QStringLiteral("^\\s*lattice\\W"),
        QStringLiteral("^\\s*region\\W"),       QStringLiteral("^\\s*create_box\\W"),
        QStringLiteral("^\\s*create_atoms\\W"), QStringLiteral("^\\s*dielectric\\W"),
        QStringLiteral("^\\s*delete_atoms\\W"), QStringLiteral("^\\s*displace_atoms\\W"),
        QStringLiteral("^\\s*change_box\\W"),   QStringLiteral("^\\s*dimension\\W"),
        QStringLiteral("^\\s*replicate\\W")};
    for (const QString &pattern : lattice_keywords) {
        rule.pattern = QRegularExpression(pattern);
        rule.format  = latticeFormat;
        highlightingRules.append(rule);
    }

    const QString particle_keywords[] = {
        QStringLiteral("^\\s*pair_coeff\\W"),     QStringLiteral("^\\s*pair_style\\W"),
        QStringLiteral("^\\s*pair_modify\\W"),    QStringLiteral("^\\s*pair_write\\W"),
        QStringLiteral("^\\s*mass\\W"),           QStringLiteral("^\\s*velocity\\W"),
        QStringLiteral("^\\s*angle_coeff\\W"),    QStringLiteral("^\\s*angle_style\\W"),
        QStringLiteral("^\\s*angle_write\\W"),    QStringLiteral("^\\s*atom_modify\\W"),
        QStringLiteral("^\\s*atom_style\\W"),     QStringLiteral("^\\s*bond_coeff\\W"),
        QStringLiteral("^\\s*bond_style\\W"),     QStringLiteral("^\\s*bond_write\\W"),
        QStringLiteral("^\\s*create_bonds\\W"),   QStringLiteral("^\\s*delete_bonds\\W"),
        QStringLiteral("^\\s*kspace_style\\W"),   QStringLiteral("^\\s*kspace_modify\\W"),
        QStringLiteral("^\\s*dihedral_style\\W"), QStringLiteral("^\\s*dihedral_coeff\\W"),
        QStringLiteral("^\\s*dihedral_write\\W"), QStringLiteral("^\\s*improper_style\\W"),
        QStringLiteral("^\\s*improper_coeff\\W"), QStringLiteral("^\\s*labelmap\\W")};
    for (const QString &pattern : particle_keywords) {
        rule.pattern = QRegularExpression(pattern);
        rule.format  = particleFormat;
        highlightingRules.append(rule);
    }

    const QString setup_keywords[] = {QStringLiteral("^\\s*min_style\\W"),
                                      QStringLiteral("^\\s*min_modify\\W"),
                                      QStringLiteral("^\\s*run_style\\W"),
                                      QStringLiteral("^\\s*timestep\\W"),
                                      QStringLiteral("^\\s*neighbor\\W"),
                                      QStringLiteral("^\\s*neigh_modify\\W"),
                                      QStringLiteral("^\\s*suffix\\W"),
                                      QStringLiteral("^\\s*special_bonds\\W"),
                                      QStringLiteral("^\\s*balance\\W"),
                                      QStringLiteral("^\\s*box\\W"),
                                      QStringLiteral("^\\s*clear\\W"),
                                      QStringLiteral("^\\s*comm_modify\\W"),
                                      QStringLiteral("^\\s*comm_style\\W"),
                                      QStringLiteral("^\\s*newton\\W"),
                                      QStringLiteral("^\\s*package\\W"),
                                      QStringLiteral("^\\s*processors\\W"),
                                      QStringLiteral("^\\s*reset_atoms\\W"),
                                      QStringLiteral("^\\s*dump_modify\\W"),
                                      QStringLiteral("^\\s*reset_ids\\W"),
                                      QStringLiteral("^\\s*reset_timestep\\W"),
                                      QStringLiteral("^\\s*label\\W"),
                                      QStringLiteral("^\\s*jump\\W"),
                                      QStringLiteral("^\\s*next\\W"),
                                      QStringLiteral("^\\s*loop\\W")

    };
    for (const QString &pattern : setup_keywords) {
        rule.pattern = QRegularExpression(pattern);
        rule.format  = setupFormat;
        highlightingRules.append(rule);
    }

    const QString run_keywords[] = {QStringLiteral("^\\s*minimize\\W"),
                                    QStringLiteral("^\\s*minimize/kk\\W"),
                                    QStringLiteral("^\\s*run\\W"),
                                    QStringLiteral("^\\s*rerun\\W"),
                                    QStringLiteral("^\\s*tad\\W"),
                                    QStringLiteral("^\\s*neb\\W"),
                                    QStringLiteral("^\\s*neb/spin\\W"),
                                    QStringLiteral("^\\s*prd\\W"),
                                    QStringLiteral("^\\s*quit\\W"),
                                    QStringLiteral("^\\s*server\\W"),
                                    QStringLiteral("^\\s*temper/npt\\W"),
                                    QStringLiteral("^\\s*temper/grem\\W"),
                                    QStringLiteral("^\\s*temper\\W"),
                                    QStringLiteral("^\\s*message\\W"),
                                    QStringLiteral("^\\s*hyper\\W"),
                                    QStringLiteral("^\\s*dynamical_matrix\\W"),
                                    QStringLiteral("^\\s*dynamical_matrix/kk\\W"),
                                    QStringLiteral("^\\s*third_order\\W"),
                                    QStringLiteral("^\\s*third_order/kk\\W"),
                                    QStringLiteral("^\\s*fitpod\\W"),
                                    QStringLiteral("^\\s*if\\W"),
                                    QStringLiteral("^\\s*then\\W"),
                                    QStringLiteral("^\\s*elif\\W"),
                                    QStringLiteral("^\\s*else\\W")};
    for (const QString &pattern : run_keywords) {
        rule.pattern = QRegularExpression(pattern);
        rule.format  = runFormat;
        highlightingRules.append(rule);
    }

    const QString define_keywords[] = {QStringLiteral("^\\s*variable\\W"),
                                       QStringLiteral("^\\s*group\\W"),
                                       QStringLiteral("^\\s*compute\\W"),
                                       QStringLiteral("^\\s*python\\W"),
                                       QStringLiteral("^\\s*set\\W"),
                                       QStringLiteral("^\\s*uncompute\\W"),
                                       QStringLiteral("^\\s*kim_query\\W"),
                                       QStringLiteral("^\\s*kim\\W"),
                                       QStringLiteral("^\\s*group2ndx\\W"),
                                       QStringLiteral("^\\s*ndx2group\\W"),
                                       QStringLiteral("^\\s*compute_modify\\W"),
                                       QStringLiteral("^\\s*fix_modify\\W"),
                                       QStringLiteral("^\\s*fix\\W"),
                                       QStringLiteral("^\\s*unfix\\W"),
                                       QStringLiteral("^\\s*INF\\W"),
                                       QStringLiteral("^\\s*EDGE\\W"),
                                       QStringLiteral("^\\s*NULL\\W"),
                                       QStringLiteral("^\\s*&\\s*$"),
                                       QStringLiteral("^\\s*mdi\\W")};
    for (const QString &pattern : define_keywords) {
        rule.pattern = QRegularExpression(pattern);
        rule.format  = defineFormat;
        highlightingRules.append(rule);
    }

    const QString number_keywords[] = {
        QStringLiteral("(^|\\s+)[0-9:*]+"),                          // integer and integer ranges
        QStringLiteral("(^|\\s+)[0-9]+\\.[0-9]*[edED]?[-+]?[0-9]*"), // floating point 1
        QStringLiteral("(^|\\s+)[0-9]*\\.[0-9]+[edED]?[-+]?[0-9]*"), // floating point 2
        QStringLiteral("(^|\\s+)[0-9]+([edED][-+]?[0-9]+)?")         // floating point 3
    };
    for (const QString &pattern : number_keywords) {
        rule.pattern = QRegularExpression(pattern);
        rule.format  = numberFormat;
        highlightingRules.append(rule);
    }

    // comments, must come before strings but after other keywords.
    rule.pattern = QRegularExpression("#.*");
    rule.format  = commentFormat;
    highlightingRules.append(rule);

    // strings, must come last so it overwrites other formatting
    rule.pattern = QRegularExpression("(\".*\"|'.*')");
    rule.format  = stringFormat;
    highlightingRules.append(rule);
}

void Highlighter::highlightBlock(const QString &text)
{
    // clang-format off
    auto style = QRegularExpression("^(fix|compute|dump|set)\\s+(\\w+)\\s+(\\S+)\\s+(\\S+)").match(text);
    auto force = QRegularExpression("^(atom_style|pair_style|bond_style|angle_style|dihedral_style|improper_style|kspace_style)\\s+(\\S+)").match(text);
    auto defs = QRegularExpression("^(group|variable)\\s+(\\S+)\\s+(\\S+)").match(text);
    auto undo = QRegularExpression("^(unfix|uncompute|undump)\\s+(\\w+)").match(text);
    // clang-format on
    bool do_style = true;
    bool do_force = true;
    bool do_defs  = true;
    bool do_undo  = true;
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            // special treatment for fix/compute/dump styles etc.
            if (style.hasMatch() && do_style) {
                setFormat(style.capturedStart(1), style.capturedLength(1), defineFormat);
                setFormat(style.capturedStart(2), style.capturedLength(2), numberFormat);
                setFormat(style.capturedStart(3), style.capturedLength(3), stringFormat);
                setFormat(style.capturedStart(4), style.capturedLength(4), runFormat);
                do_style = false;
                // special treatment for force styles styles
            } else if (force.hasMatch() && do_force) {
                setFormat(force.capturedStart(1), force.capturedLength(1), particleFormat);
                setFormat(force.capturedStart(2), force.capturedLength(2), runFormat);
                do_force = false;
                // special treatment for undo commands
            } else if (undo.hasMatch() && do_undo) {
                setFormat(undo.capturedStart(1), undo.capturedLength(1), defineFormat);
                setFormat(undo.capturedStart(2), undo.capturedLength(2), stringFormat);
                do_undo = false;
                // special treatment for some definitions
            } else if (defs.hasMatch() && do_defs) {
                setFormat(defs.capturedStart(1), defs.capturedLength(1), particleFormat);
                setFormat(defs.capturedStart(2), defs.capturedLength(2), stringFormat);
                setFormat(defs.capturedStart(3), defs.capturedLength(3), runFormat);
                do_defs = false;
            } else {
                setFormat(match.capturedStart(), match.capturedLength(), rule.format);
            }
        }
    }
}
// Local Variables:
// c-basic-offset: 4
// End:
