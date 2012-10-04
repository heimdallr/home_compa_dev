object dmConnectKeeper: TdmConnectKeeper
  OldCreateOrder = False
  OnDestroy = DataModuleDestroy
  Left = 356
  Top = 128
  Height = 150
  Width = 215
  object Timer: TTimer
    Enabled = False
    OnTimer = TimerTimer
    Left = 24
    Top = 12
  end
end
