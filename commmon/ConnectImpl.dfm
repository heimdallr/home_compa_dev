inherited dmConnectImpl: TdmConnectImpl
  OldCreateOrder = True
  OnDestroy = DataModuleDestroy
  Left = 1006
  Top = 86
  Height = 325
  Width = 550
  object Database: TIBDatabase
    LoginPrompt = False
    DefaultTransaction = trRead
    IdleTimer = 0
    SQLDialect = 3
    TraceFlags = []
    Left = 40
    Top = 12
  end
  object trRead: TIBTransaction
    Active = False
    DefaultDatabase = Database
    Params.Strings = (
      'read'
      'read_committed'
      'rec_version')
    AutoStopAction = saNone
    Left = 92
    Top = 12
  end
  object sqlRead: TIBSQL
    Database = Database
    ParamCheck = True
    Transaction = trRead
    Left = 96
    Top = 120
  end
  object dsRead: TIBClientDataSet
    Aggregates = <>
    Options = [poAllowCommandText]
    Params = <>
    DBConnection = Database
    DBTransaction = trRead
    Left = 96
    Top = 64
  end
  object Events: TIBEvents
    AutoRegister = False
    Database = Database
    Registered = False
    Left = 44
    Top = 68
  end
  object dsWrite: TIBClientDataSet
    Aggregates = <>
    Options = [poAllowCommandText]
    Params = <>
    DBConnection = Database
    DBTransaction = trWrite
    Left = 148
    Top = 68
  end
  object trWrite: TIBTransaction
    Active = False
    DefaultDatabase = Database
    Params.Strings = (
      'read_committed'
      'rec_version'
      'nowait')
    AutoStopAction = saNone
    Left = 144
    Top = 12
  end
end
