#ifndef URLLINEEDIT_H
#define URLLINEEDIT_H

#include <QtCore/QUrl>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStyleOptionFrame>

class QLineEdit;

class ClearButton;
class ExLineEdit : public QWidget
{
    Q_OBJECT

public:
    ExLineEdit(QWidget *parent = 0);

    inline QLineEdit *lineEdit() const { return m_lineEdit; }

    void setLeftWidget(QWidget *widget);
    QWidget *leftWidget() const;

    QSize sizeHint() const;

    QVariant inputMethodQuery(Qt::InputMethodQuery property) const;
protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void inputMethodEvent(QInputMethodEvent *e);
    bool event(QEvent *event);

protected:
    void updateGeometries();
    void initStyleOption(QStyleOptionFrame *option) const;

    QWidget *m_leftWidget;
    QLineEdit *m_lineEdit;
    ClearButton *m_clearButton;
};

class UrlIconLabel;
class WebView;
class UrlLineEdit : public ExLineEdit
{
    Q_OBJECT

public:
    UrlLineEdit(QWidget *parent = 0);
    void setWebView(WebView *webView);

protected:
    void paintEvent(QPaintEvent *event);
    void focusOutEvent(QFocusEvent *event);

private slots:
    void webViewUrlChanged(const QUrl &url);
    void webViewIconChanged(const QIcon &icon);

private:
    QLinearGradient generateGradient(const QColor &color) const;
    WebView *m_webView;
    UrlIconLabel *m_iconLabel;
    QColor m_defaultBaseColor;

};

#endif // URLLINEEDIT_H
