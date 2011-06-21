#include "view.h"
#include "imgclass.h"
#include <QFileInfo>
#include <QDir>
/*
View::View(QString path)
{
    QFileInfo inf(path);

    if (inf.exists())
    {
        QString suffix;
        suffix = inf.suffix().toLower();
        if (suffix == "jpeg" ||
                suffix == "jpg" ||
                suffix == "bmp" ||
                suffix == "png" ||
                suffix == "gif")
            this->img.load(path);
        //emit this->ready;
    }
}
*/
QString View::getImgDir()
{
    QString dirPath = QDir::tempPath() +
            QDir::separator() +
            "KBookOCR.tmp.imgs" + QDir::separator();
    QDir dir(dirPath);
    if (!dir.exists())
        dir.mkdir(dirPath);
    return dirPath;
}

bool View::setView(const QImage &img)
{
    if (img != this->getView() &&
            img.width() > 100 &&
            img.height() > 100)
    {

    //    this->img = img;

        QString imgPath;
        QFileInfo* inf = 0;
        do
        {
            imgPath = this->getImgDir() + QString::number(rand()) + ".jpg";
            if (inf)
                delete inf;
            inf = new QFileInfo(imgPath);
        }
        while (inf->exists());
        img.save(imgPath);
        this->path = imgPath;

        return true;
    }
    return false;
}

View::View(QImage img, Document* doc, int page)
{
    this->setView(img);
    this->doc = doc;
    this->realPage = page;
}

View::View(Document *doc, int n) :
    doc(0),
    page(n),
    realPage(n)
{
    if (doc->isOpened() && doc->getPageCount()+1 > n && n > 0)
    {
        this->doc = doc;
        this->setView(doc->getPage(n));

        //doc->getRealPage(n).save("/tmp/1.jpg");
        //this->doc->page(n)->renderToImage(
          //                  doc->page(n)->pageSize().width()
            //                ,doc->page(n)->pageSize().height());

        //connect(doc,SIGNAL(pageIsReady(QImage)),this,SLOT(imgForViewReady(QImage)));
    }
}
/*
void View::imgForViewReady(QImage img)
{
    if (this->img.isNull())
    {
        this->setView(img);
        //emit this->ready();
    }
    //disconnect(doc,SIGNAL(pageIsReady(QImage)),this,SLOT(imgForViewReady(QImage)));
}
*/
QImage View::getView()
{
    //return this->img;
    QImage img;
    img.load(this->path);
    return img;

}

QImage View::getPreview(QSize size)
{
    return this->getView().scaled(size);
    //return this->doc->getPreview(this->page);
}
