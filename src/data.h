class DataManager
{
public:
    explicit DataManager(const QString &path);
private:
    QSqlDatabase db;
};

