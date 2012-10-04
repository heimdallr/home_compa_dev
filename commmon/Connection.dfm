object dmConnect: TdmConnect
  OldCreateOrder = False
  OnDestroy = DataModuleDestroy
  Left = 247
  Top = 176
  Height = 210
  Width = 324
  object Database: TIBDatabase
    DatabaseName = ':'
    LoginPrompt = False
    DefaultTransaction = trRead
    IdleTimer = 0
    SQLDialect = 3
    TraceFlags = []
    Left = 28
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
    Left = 80
    Top = 16
  end
  object sqlRead: TIBSQL
    Database = Database
    ParamCheck = True
    Transaction = trRead
    Left = 28
    Top = 72
  end
  object Query: TIBQuery
    Database = Database
    Transaction = trRead
    BufferChunks = 1000
    CachedUpdates = False
    Left = 80
    Top = 68
  end
  object Events: TIBEvents
    AutoRegister = False
    Database = Database
    Registered = False
    OnEventAlert = EventsEventAlert
    Left = 28
    Top = 128
  end
  object dsEvent: TClientDataSet
    Aggregates = <>
    Params = <>
    Left = 140
    Top = 20
    object dsEventName: TStringField
      FieldName = 'Name'
      Size = 127
    end
    object dsEventAlert: TIntegerField
      FieldName = 'Alert'
    end
  end
end
