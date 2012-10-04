object fmDates: TfmDates
  Left = 273
  Top = 101
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'fmDates'
  ClientHeight = 542
  ClientWidth = 954
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object pnlButton: TPanel
    Left = 0
    Top = 369
    Width = 868
    Height = 125
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      868
      125)
    object btnOk: TBitBtn
      Left = 49
      Top = 0
      Width = 154
      Height = 31
      Action = actOk
      Anchors = [akTop]
      Caption = #1054#1050
      TabOrder = 0
      Kind = bkOK
    end
    object btnCancel: TBitBtn
      Left = 354
      Top = 0
      Width = 154
      Height = 31
      Action = actCancel
      Anchors = [akTop]
      Cancel = True
      Caption = #1054#1090#1084#1077#1085#1072
      TabOrder = 1
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00388888888877
        F7F787F8888888888333333F00004444400888FFF444448888888888F333FF8F
        000033334D5007FFF4333388888888883338888F0000333345D50FFFF4333333
        338F888F3338F33F000033334D5D0FFFF43333333388788F3338F33F00003333
        45D50FEFE4333333338F878F3338F33F000033334D5D0FFFF43333333388788F
        3338F33F0000333345D50FEFE4333333338F878F3338F33F000033334D5D0FFF
        F43333333388788F3338F33F0000333345D50FEFE4333333338F878F3338F33F
        000033334D5D0EFEF43333333388788F3338F33F0000333345D50FEFE4333333
        338F878F3338F33F000033334D5D0EFEF43333333388788F3338F33F00003333
        4444444444333333338F8F8FFFF8F33F00003333333333333333333333888888
        8888333F00003333330000003333333333333FFFFFF3333F00003333330AAAA0
        333333333333888888F3333F00003333330000003333333333338FFFF8F3333F
        0000}
      NumGlyphs = 2
    end
  end
  object pnlDate: TPanel
    Left = 0
    Top = 0
    Width = 897
    Height = 321
    BevelOuter = bvNone
    TabOrder = 1
    object pnlFrom: TPanel
      Left = 0
      Top = 0
      Width = 262
      Height = 233
      BevelOuter = bvNone
      TabOrder = 0
      object mcFrom: TMonthCalendar
        Left = 20
        Top = 20
        Width = 176
        Height = 183
        AutoSize = True
        Date = 38821.6328525
        TabOrder = 0
        OnClick = mcFromClick
      end
    end
    object pnlTo: TPanel
      Left = 281
      Top = 0
      Width = 306
      Height = 218
      BevelOuter = bvNone
      TabOrder = 1
      object mcTo: TMonthCalendar
        Left = 30
        Top = 10
        Width = 176
        Height = 183
        AutoSize = True
        Date = 38821.6328525
        TabOrder = 0
        OnClick = mcToClick
      end
    end
  end
  object ActionList1: TActionList
    Left = 12
    Top = 8
    object actOk: TAction
      Caption = #1054#1050
      ShortCut = 16397
      OnExecute = actOkExecute
    end
    object actCancel: TAction
      Caption = #1054#1090#1084#1077#1085#1072
      ShortCut = 8219
      OnExecute = actCancelExecute
    end
  end
end
