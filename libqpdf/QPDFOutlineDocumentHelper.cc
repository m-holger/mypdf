#include <qpdf/QPDFOutlineDocumentHelper.hh>

#include <qpdf/QTC.hh>

QPDFOutlineDocumentHelper::QPDFOutlineDocumentHelper(QPDF& qpdf) :
    QPDFDocumentHelper(qpdf),
    m(new Members())
{
    QPDFObjectHandle root = qpdf.getRoot();
    if (!root.hasKey("/Outlines")) {
        return;
    }
    QPDFObjectHandle outlines = root.getKey("/Outlines");
    if (!(outlines.isDictionary() && outlines.hasKey("/First"))) {
        return;
    }
    QPDFObjectHandle cur = outlines.getKey("/First");
    QPDFObjGen::set seen;
    while (!cur.isNull() && seen.add(cur)) {
        m->outlines.push_back(QPDFOutlineObjectHelper::Accessor::create(cur, *this, 1));
        cur = cur.getKey("/Next");
    }
}

bool
QPDFOutlineDocumentHelper::hasOutlines()
{
    return !m->outlines.empty();
}

std::vector<QPDFOutlineObjectHelper>
QPDFOutlineDocumentHelper::getTopLevelOutlines()
{
    return m->outlines;
}

void
QPDFOutlineDocumentHelper::initializeByPage()
{
    std::list<QPDFOutlineObjectHelper> queue;
    queue.insert(queue.end(), m->outlines.begin(), m->outlines.end());

    while (!queue.empty()) {
        QPDFOutlineObjectHelper oh = queue.front();
        queue.pop_front();
        m->by_page[oh.getDestPage().getObjGen()].push_back(oh);
        std::vector<QPDFOutlineObjectHelper> kids = oh.getKids();
        queue.insert(queue.end(), kids.begin(), kids.end());
    }
}

std::vector<QPDFOutlineObjectHelper>
QPDFOutlineDocumentHelper::getOutlinesForPage(QPDFObjGen const& og)
{
    if (m->by_page.empty()) {
        initializeByPage();
    }
    std::vector<QPDFOutlineObjectHelper> result;
    if (m->by_page.count(og)) {
        result = m->by_page[og];
    }
    return result;
}

QPDFObjectHandle
QPDFOutlineDocumentHelper::resolveNamedDest(QPDFObjectHandle name)
{
    QPDFObjectHandle result;
    if (name.isName()) {
        if (!m->dest_dict.isInitialized()) {
            m->dest_dict = this->qpdf.getRoot().getKey("/Dests");
        }
        if (m->dest_dict.isDictionary()) {
            QTC::TC("qpdf", "QPDFOutlineDocumentHelper name named dest");
            result = m->dest_dict.getKey(name.getName());
        }
    } else if (name.isString()) {
        if (nullptr == m->names_dest) {
            QPDFObjectHandle names = this->qpdf.getRoot().getKey("/Names");
            if (names.isDictionary()) {
                QPDFObjectHandle dests = names.getKey("/Dests");
                if (dests.isDictionary()) {
                    m->names_dest = std::make_shared<QPDFNameTreeObjectHelper>(dests, this->qpdf);
                }
            }
        }
        if (m->names_dest.get()) {
            if (m->names_dest->findObject(name.getUTF8Value(), result)) {
                QTC::TC("qpdf", "QPDFOutlineDocumentHelper string named dest");
            }
        }
    }
#ifndef QPDF_FUTURE
    if (!result.isInitialized()) {
        result = QPDFObjectHandle::newNull();
    }
#endif
    return result;
}
