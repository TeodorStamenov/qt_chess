#include "CapturedPieces.h"
#include "GameManager.h"


CapturedPieces::CapturedPieces(QObject* ui, GameManager& manager)
    : manager_(manager)
{
    QObject::connect(this, SIGNAL(sendCapturedPiece(QVariant))
                     ,ui ,SLOT(capturedPiece(QVariant)));

    QObject::connect(this, SIGNAL(sendCleanPieces())
                     ,ui ,SLOT(cleanPieces()));
}

void CapturedPieces::onCapturedPiece(const QChar pieceSymbol)
{
    capturedPieces_.append(pieceSymbol);
    emit sendCapturedPiece(QVariant::fromValue(pieceSymbol));
}

void CapturedPieces::clean()
{
    capturedPieces_.clear();
    emit sendCleanPieces();
}

const QString& CapturedPieces::getCapturedPieces() const
{
    return capturedPieces_;
}

void CapturedPieces::setCaptutedPieces(const QString& capturedPieces)
{
    capturedPieces_ = capturedPieces;
    emit sendCapturedPiece(QVariant::fromValue(capturedPieces));
}
