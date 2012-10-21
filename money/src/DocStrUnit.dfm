object fmDocStr: TfmDocStr
  Left = 986
  Top = 55
  Width = 424
  Height = 447
  BorderIcons = [biMinimize, biMaximize]
  Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1089#1090#1088#1086#1082#1080
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnDestroy = FormDestroy
  OnPaint = FormPaint
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object gbNote: TGroupBox
    Left = 0
    Top = 0
    Width = 416
    Height = 53
    Align = alTop
    Caption = #1055#1088#1080#1084#1077#1095#1072#1085#1080#1077
    TabOrder = 0
    object pnlNote: TPanel
      Left = 2
      Top = 15
      Width = 412
      Height = 36
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 0
      DesignSize = (
        412
        36)
      object eNote: TEdit
        Left = 8
        Top = 4
        Width = 398
        Height = 21
        Anchors = [akLeft, akTop, akRight, akBottom]
        TabOrder = 0
        OnKeyPress = eQtyKeyPress
      end
    end
  end
  object gbQty: TGroupBox
    Left = 0
    Top = 264
    Width = 416
    Height = 53
    Align = alBottom
    Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086', '#1089#1091#1084#1084#1072
    TabOrder = 2
    object pnlBtnSaveSumma: TPanel
      Left = 380
      Top = 15
      Width = 34
      Height = 36
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      object SpeedButton1: TSpeedButton
        Left = 4
        Top = 4
        Width = 23
        Height = 22
        Action = actSetQty
        Flat = True
      end
    end
    object pnlQtySumma: TPanel
      Left = 2
      Top = 15
      Width = 378
      Height = 36
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
      object pnlQty: TPanel
        Left = 0
        Top = 0
        Width = 226
        Height = 36
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        DesignSize = (
          226
          36)
        object eQty: TDBEditEh
          Left = 8
          Top = 4
          Width = 209
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          DataField = 'Qty'
          DataSource = dsrcSumma
          EditButtons = <>
          TabOrder = 0
          Visible = True
          OnKeyPress = eQtyKeyPress
        end
      end
      object pnlSumma: TPanel
        Left = 226
        Top = 0
        Width = 152
        Height = 36
        Align = alRight
        BevelOuter = bvNone
        TabOrder = 1
        DesignSize = (
          152
          36)
        object eSumma: TDBEditEh
          Left = 4
          Top = 4
          Width = 141
          Height = 21
          Anchors = [akLeft, akTop, akRight, akBottom]
          DataField = 'Summa'
          DataSource = dsrcSumma
          EditButtons = <>
          TabOrder = 0
          Visible = True
          OnEnter = eSummaEnter
          OnExit = eSummaExit
          OnKeyPress = eSummaKeyPress
        end
      end
    end
  end
  object gbType: TGroupBox
    Left = 0
    Top = 53
    Width = 416
    Height = 211
    Align = alClient
    Caption = #1057#1090#1072#1090#1100#1103
    TabOrder = 1
    object pnlType: TPanel
      Left = 2
      Top = 15
      Width = 412
      Height = 194
      Align = alClient
      BevelInner = bvLowered
      BevelOuter = bvNone
      BorderWidth = 8
      TabOrder = 0
    end
  end
  object gbTarget: TGroupBox
    Left = 0
    Top = 317
    Width = 416
    Height = 53
    Align = alBottom
    Caption = '"'#1042#1080#1085#1086#1074#1085#1080#1082'" '#1092#1080#1085#1072#1085#1089#1086#1074#1086#1075#1086' '#1087#1086#1090#1086#1082#1072
    TabOrder = 3
    object pnlTarget: TPanel
      Left = 2
      Top = 15
      Width = 412
      Height = 36
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 0
      DesignSize = (
        412
        36)
      object lcbTarget: TDBLookupComboboxEh
        Left = 8
        Top = 4
        Width = 398
        Height = 21
        Anchors = [akLeft, akTop, akRight, akBottom]
        EditButtons = <>
        KeyField = 'id'
        ListField = 'name'
        ListSource = dsrcTarget
        TabOrder = 0
        Visible = True
        OnKeyPress = eQtyKeyPress
      end
    end
  end
  object pnlBtn: TPanel
    Left = 0
    Top = 370
    Width = 416
    Height = 47
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 4
    DesignSize = (
      416
      47)
    object btnOk: TBitBtn
      Left = 24
      Top = 12
      Width = 151
      Height = 25
      Action = actOk
      Anchors = [akLeft, akTop, akRight]
      Caption = 'OK'
      TabOrder = 0
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        3333333333333333333333330000333333333333333333333333F33333333333
        00003333344333333333333333388F3333333333000033334224333333333333
        338338F3333333330000333422224333333333333833338F3333333300003342
        222224333333333383333338F3333333000034222A22224333333338F338F333
        8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
        33333338F83338F338F33333000033A33333A222433333338333338F338F3333
        0000333333333A222433333333333338F338F33300003333333333A222433333
        333333338F338F33000033333333333A222433333333333338F338F300003333
        33333333A222433333333333338F338F00003333333333333A22433333333333
        3338F38F000033333333333333A223333333333333338F830000333333333333
        333A333333333333333338330000333333333333333333333333333333333333
        0000}
      NumGlyphs = 2
    end
    object btnCancel: TBitBtn
      Left = 244
      Top = 12
      Width = 151
      Height = 25
      Action = actCancel
      Anchors = [akLeft, akTop, akRight]
      Caption = #1054#1090#1084#1077#1085#1072
      TabOrder = 1
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        333333333333333333333333000033338833333333333333333F333333333333
        0000333911833333983333333388F333333F3333000033391118333911833333
        38F38F333F88F33300003339111183911118333338F338F3F8338F3300003333
        911118111118333338F3338F833338F3000033333911111111833333338F3338
        3333F8330000333333911111183333333338F333333F83330000333333311111
        8333333333338F3333383333000033333339111183333333333338F333833333
        00003333339111118333333333333833338F3333000033333911181118333333
        33338333338F333300003333911183911183333333383338F338F33300003333
        9118333911183333338F33838F338F33000033333913333391113333338FF833
        38F338F300003333333333333919333333388333338FFF830000333333333333
        3333333333333333333888330000333333333333333333333333333333333333
        0000}
      NumGlyphs = 2
    end
  end
  object alMain: TActionList
    Left = 372
    Top = 24
    object actOk: TAction
      Caption = 'OK'
      ShortCut = 16397
    end
    object actCancel: TAction
      Caption = #1054#1090#1084#1077#1085#1072
      ShortCut = 8219
      OnExecute = actCancelExecute
    end
    object actSetQty: TAction
      Caption = '...'
      OnExecute = actSetQtyExecute
    end
    object actOkNew: TAction
      Caption = 'actOkNew'
      OnExecute = actOkNewExecute
    end
    object actOkEdit: TAction
      Caption = 'actOkEdit'
      OnExecute = actOkEditExecute
    end
    object actLeft: TAction
      Caption = 'actLeft'
      ShortCut = 37
      OnExecute = actLeftExecute
    end
    object actRight: TAction
      Caption = 'actRight'
      ShortCut = 39
      OnExecute = actRightExecute
    end
    object actMul: TAction
      Caption = 'actMul'
      ShortCut = 16461
      OnExecute = actMulExecute
    end
  end
  object dsrcTarget: TDataSource
    DataSet = dsTarget
    Left = 344
    Top = 332
  end
  object dsTarget: TClientDataSet
    Aggregates = <>
    Params = <>
    Left = 372
    Top = 332
  end
  object dsrcSumma: TDataSource
    DataSet = dsSumma
    Left = 292
    Top = 280
  end
  object dsSumma: TClientDataSet
    Aggregates = <>
    Params = <>
    Left = 320
    Top = 280
    object dsSummaSumma: TCurrencyField
      FieldName = 'Summa'
    end
    object dsSummaQty: TFloatField
      FieldName = 'Qty'
    end
  end
end
