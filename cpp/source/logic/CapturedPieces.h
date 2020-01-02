#pragma once

#include <QObject>
#include <QVariant>

class GameManager;

class CapturedPieces : public QObject
{
    Q_OBJECT
public:
    CapturedPieces(QObject* ui, GameManager& manager);

    void onCapturedPiece(const QChar pieceSymbol);
    void clean();
    const QString&  getCapturedPieces() const;
    void setCaptutedPieces(const QString& capturedPieces);

signals:
    void sendCapturedPiece(QVariant piece);
    void sendCleanPieces();

private:
    GameManager& manager_;
    QString capturedPieces_;
};
