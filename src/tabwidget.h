#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QtWebEngineWidgets/QWebEngineFullScreenRequest>
#include <QtWidgets/QTabBar>
#include <QtWidgets/QShortcut>

class QWebEngineDownloadItem;
class QWebEngineProfile;
class QWebEngineView;

/*
    Tab bar with a few more features such as a context menu and shortcuts
 */
class TabBar : public QTabBar
{
    Q_OBJECT

signals:
    void newTab();
    void cloneTab(int index);
    void closeTab(int index);
    void closeOtherTabs(int index);
    void reloadTab(int index);
    void muteTab(int index, bool mute);
    void reloadAllTabs();
    void tabMoveRequested(int fromIndex, int toIndex);

public:
    TabBar(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private slots:
    void selectTabAction();
    void cloneTab();
    void closeTab();
    void closeOtherTabs();
    void reloadTab();
    void muteTab();
    void unmuteTab();
    void contextMenuRequested(const QPoint &position);

private:
    QList<QShortcut*> m_tabShortcuts;
    friend class TabWidget;

    QPoint m_dragStartPos;
    int m_dragCurrentIndex;
};

#include <QWebEnginePage>

class QAction;

class WebView;
/*!
    A proxy object that connects a single browser action
    to one child webpage action at a time.

    Example usage: used to keep the main window stop action in sync with
    the current tabs webview's stop action.
 */
class WebActionMapper : public QObject
{
    Q_OBJECT

public:
    WebActionMapper(QAction *root, QWebEnginePage::WebAction webAction, QObject *parent);
    QWebEnginePage::WebAction webAction() const;
    void addChild(QAction *action);
    void updateCurrent(QWebEnginePage *currentParent);

private slots:
    void rootTriggered();
    void childChanged();
    void rootDestroyed();
    void currentDestroyed();

private:
    QWebEnginePage *m_currentParent;
    QAction *m_root;
    QWebEnginePage::WebAction m_webAction;
};

#include <QtCore/QUrl>
#include <QtWidgets/QTabWidget>

class FullScreenNotification;

class QCompleter;
class QLineEdit;
class QMenu;
class QStackedWidget;

/*!
    TabWidget that contains WebViews and a stack widget of associated line edits.

    Connects up the current tab's signals to this class's signal and uses WebActionMapper
    to proxy the actions.
 */
class TabWidget : public QTabWidget
{
    Q_OBJECT

signals:
    // tab widget signals
    void loadPage(const QString &url);
    void tabsChanged();
    void lastTabClosed();

    // current tab signals
    void setCurrentTitle(const QString &url);
    void showStatusBarMessage(const QString &message);
    void linkHovered(const QString &link);
    void loadProgress(int progress);
    void geometryChangeRequested(const QRect &geometry);
    void menuBarVisibilityChangeRequested(bool visible);
    void statusBarVisibilityChangeRequested(bool visible);
    void toolBarVisibilityChangeRequested(bool visible);
#if defined(QWEBENGINEPAGE_PRINTREQUESTED)
    void printRequested(QWebEngineFrame *frame);
#endif

public:
    TabWidget(QWidget *parent = 0);
    ~TabWidget();
    void clear();
    void addWebAction(QAction *action, QWebEnginePage::WebAction webAction);

    QAction *newTabAction() const;
    QAction *closeTabAction() const;
    QAction *recentlyClosedTabsAction() const;
    QAction *nextTabAction() const;
    QAction *previousTabAction() const;

    QWidget *lineEditStack() const;
    QLineEdit *currentLineEdit() const;
    WebView *currentWebView() const;
    WebView *webView(int index) const;
    QLineEdit *lineEdit(int index) const;
    int webViewIndex(WebView *webView) const;

    QByteArray saveState() const;
    bool restoreState(const QByteArray &state);

    void setProfile(QWebEngineProfile *profile);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void loadUrlInCurrentTab(const QUrl &url);
    WebView *newTab(bool makeCurrent = true);
    void cloneTab(int index = -1);
    void requestCloseTab(int index = -1);
    void closeTab(int index);
    void closeOtherTabs(int index);
    void reloadTab(int index = -1);
    void reloadAllTabs();
    void nextTab();
    void previousTab();
    void setAudioMutedForTab(int index, bool mute);

private slots:
    void currentChanged(int index);
    void aboutToShowRecentTabsMenu();
    void aboutToShowRecentTriggeredAction(QAction *action);
    void downloadRequested(QWebEngineDownloadItem *download);
    void webViewLoadStarted();
    void webViewIconChanged(const QIcon &icon);
    void webViewTitleChanged(const QString &title);
    void webViewUrlChanged(const QUrl &url);
    void lineEditReturnPressed();
    void windowCloseRequested();
    void moveTab(int fromIndex, int toIndex);
    void fullScreenRequested(QWebEngineFullScreenRequest request);
    void handleTabBarDoubleClicked(int index);
    void webPageMutedOrAudibleChanged();

private:
    void setupPage(QWebEnginePage* page);

    QAction *m_recentlyClosedTabsAction;
    QAction *m_newTabAction;
    QAction *m_closeTabAction;
    QAction *m_nextTabAction;
    QAction *m_previousTabAction;

    QMenu *m_recentlyClosedTabsMenu;
    static const int m_recentlyClosedTabsSize = 10;
    QList<QUrl> m_recentlyClosedTabs;
    QList<WebActionMapper*> m_actions;

    QCompleter *m_lineEditCompleter;
    QStackedWidget *m_lineEdits;
    TabBar *m_tabBar;
    QWebEngineProfile *m_profile;
    QWebEngineView *m_fullScreenView;
    FullScreenNotification *m_fullScreenNotification;
};

#endif // TABWIDGET_H
