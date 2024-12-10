#ifndef Q_PROP_H
#define Q_PROP_H

///
#define PROP_READ_WRITE_MEMBER_H(type, lower, UPPER)                         \
private:                                                                     \
    Q_PROPERTY(type lower READ lower WRITE set##UPPER NOTIFY lower##Changed) \
    type m_##lower;                                                          \
                                                                             \
public:                                                                      \
    type lower() const;                                                      \
    void set##UPPER(type lower);                                             \
Q_SIGNALS:                                                                   \
    void lower##Changed();

#define PROP_READ_WRITE_MEMBER_CPP(type, lower, UPPER, CLASS) \
    type CLASS::lower() const                                 \
    {                                                         \
        return m_##lower;                                     \
    }                                                         \
    void CLASS::set##UPPER(type lower)                        \
    {                                                         \
        m_##lower = lower;                                    \
        emit lower##Changed();                                \
    }

///
#define PROP_READ_QMLWRITE_MEMBER_H(type, lower, UPPER)                      \
private:                                                                     \
    Q_PROPERTY(type lower READ lower WRITE set##UPPER NOTIFY lower##Changed) \
    type m_##lower;                                                          \
                                                                             \
public:                                                                      \
    type lower() const;                                                      \
    Q_INVOKABLE void set##UPPER(type lower);                                 \
Q_SIGNALS:                                                                   \
    void lower##Changed();


#define PROP_READ_WRITE_MEMBER_CPP(type, lower, UPPER, CLASS) \
    type CLASS::lower() const                                 \
    {                                                         \
        return m_##lower;                                     \
    }                                                         \
    void CLASS::set##UPPER(type lower)                        \
    {                                                         \
        m_##lower = lower;                                    \
        emit lower##Changed();                                \
    }

///
#define PROP_READ_H(type, lower)                            \
private:                                                    \
    Q_PROPERTY(type lower READ lower NOTIFY lower##Changed) \
                                                            \
public:                                                     \
    type lower() const;                                     \
Q_SIGNALS:                                                  \
    void lower##Changed();

#endif //Q_PROP_H
