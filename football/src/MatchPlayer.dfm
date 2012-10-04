object fmPlayer: TfmPlayer
  Left = 1027
  Top = 117
  Width = 870
  Height = 640
  Caption = 'fmPlayer'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poMainFormCenter
  Visible = True
  WindowState = wsMaximized
  OnClose = FormClose
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object pnlPlayer2: TGroupBox
    Left = 0
    Top = 215
    Width = 862
    Height = 395
    Align = alClient
    Caption = 'pnlPlayer2'
    TabOrder = 1
    object dbgChamp2: TDBGridEh
      Tag = 1
      Left = 8
      Top = 16
      Width = 272
      Height = 371
      Align = alLeft
      AllowedOperations = []
      Ctl3D = False
      DataGrouping.GroupLevels = <>
      DataSource = dsrcChamp2
      Flat = True
      FooterColor = clBtnFace
      FooterFont.Charset = DEFAULT_CHARSET
      FooterFont.Color = clWindowText
      FooterFont.Height = -10
      FooterFont.Name = 'MS Sans Serif'
      FooterFont.Style = []
      FooterRowCount = 1
      HorzScrollBar.Visible = False
      IndicatorOptions = [gioShowRowIndicatorEh]
      Options = [dgTitles, dgIndicator, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
      OptionsEh = [dghFixed3D, dghHighlightFocus, dghClearSelection, dghIncSearch, dghPreferIncSearch, dghDialogFind, dghColumnResize, dghExtendVertLines]
      ParentCtl3D = False
      PopupMenu = pmChamp
      ReadOnly = True
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -10
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      UseMultiTitle = True
      VertScrollBar.VisibleMode = sbNeverShowEh
      OnDblClick = actAddExecute
      OnEnter = dbgChampMatchEnter
      OnGetCellParams = dbgGetCellParams
      Columns = <
        item
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'NUMBER'
          Footers = <>
          Title.Caption = #8470
          Width = 20
        end
        item
          EditButtons = <>
          FieldName = 'NAME'
          Footer.Value = #1047#1072#1084#1077#1085#1099':'
          Footer.ValueType = fvtStaticText
          Footers = <>
          Title.Caption = #1048#1075#1088#1086#1082#1080'|'#1048#1084#1103
          Width = 39
        end
        item
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'PLAYER_TYPE'
          Footers = <>
          Title.Caption = #1048#1075#1088#1086#1082#1080'|'#1040#1084#1087#1083#1091#1072
          Width = 105
        end
        item
          Alignment = taCenter
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'GOAL_COUNT'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          Footers = <>
          Title.Caption = #1043#1086#1083#1099'|'#1050#1086#1083'-'#1074#1086
          Width = 52
        end
        item
          Alignment = taCenter
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'GOAL_MINUTE'
          Footers = <>
          Title.Caption = #1043#1086#1083#1099'|'#1052#1080#1085#1091#1090#1072
          Width = 52
        end>
      object RowDetailData: TRowDetailPanelControlEh
      end
    end
    object dbgMatch2: TDBGridEh
      Tag = 1
      Left = 287
      Top = 16
      Width = 566
      Height = 371
      Align = alClient
      AllowedOperations = []
      Ctl3D = False
      DataGrouping.GroupLevels = <>
      DataSource = dsrcMatch2
      Flat = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      FooterColor = clBtnFace
      FooterFont.Charset = DEFAULT_CHARSET
      FooterFont.Color = clWindowText
      FooterFont.Height = -11
      FooterFont.Name = 'MS Sans Serif'
      FooterFont.Style = []
      FooterRowCount = 1
      HorzScrollBar.Visible = False
      IndicatorOptions = [gioShowRowIndicatorEh]
      Options = [dgTitles, dgIndicator, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
      OptionsEh = [dghFixed3D, dghHighlightFocus, dghClearSelection, dghIncSearch, dghPreferIncSearch, dghDialogFind, dghColumnResize, dghExtendVertLines]
      ParentCtl3D = False
      ParentFont = False
      PopupMenu = pmMatch
      ReadOnly = True
      SumList.Active = True
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      UseMultiTitle = True
      VertScrollBar.VisibleMode = sbNeverShowEh
      OnEnter = dbgChampMatchEnter
      OnGetCellParams = dbgGetCellParams
      Columns = <
        item
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'NUMBER'
          Footer.FieldName = 'NUMBER'
          Footers = <>
          Title.Caption = #8470
          Width = 27
        end
        item
          EditButtons = <>
          FieldName = 'NAME'
          Footer.Alignment = taRightJustify
          Footer.FieldName = 'NUMBER'
          Footer.ValueType = fvtCount
          Footers = <>
          Title.Caption = #1048#1075#1088#1086#1082#1080'|'#1048#1084#1103
          Width = 85
        end
        item
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'PLAYER_TYPE'
          Footers = <>
          Title.Caption = #1048#1075#1088#1086#1082#1080'|'#1040#1084#1087#1083#1091#1072
          Width = 106
        end
        item
          Alignment = taCenter
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'GOAL_COUNT'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          Footers = <>
          Title.Caption = #1043#1086#1083#1099'|'#1050#1086#1083'-'#1074#1086
          Width = 52
        end
        item
          Alignment = taCenter
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'GOAL_MINUTE'
          Footers = <>
          Title.Caption = #1043#1086#1083#1099'|'#1052#1080#1085#1091#1090#1072
          Width = 52
        end>
      object RowDetailData: TRowDetailPanelControlEh
      end
    end
    object pnlBottom2: TPanel
      Left = 2
      Top = 387
      Width = 858
      Height = 6
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 2
    end
    object pnlLeft2: TPanel
      Left = 2
      Top = 16
      Width = 6
      Height = 371
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 3
    end
    object pnlMiddle2: TPanel
      Left = 280
      Top = 16
      Width = 7
      Height = 371
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 4
    end
    object pnlRight2: TPanel
      Left = 853
      Top = 16
      Width = 7
      Height = 371
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 5
    end
    object pnlTop2: TPanel
      Left = 2
      Top = 15
      Width = 858
      Height = 1
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 6
    end
  end
  object pnlPlayer1: TGroupBox
    Left = 0
    Top = 3
    Width = 862
    Height = 206
    Align = alTop
    Caption = 'pnlPlayer1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object dbgChamp1: TDBGridEh
      Left = 8
      Top = 16
      Width = 271
      Height = 181
      Align = alLeft
      AllowedOperations = []
      Ctl3D = False
      DataGrouping.GroupLevels = <>
      DataSource = dsrcChamp1
      Flat = True
      FooterColor = clBtnFace
      FooterFont.Charset = DEFAULT_CHARSET
      FooterFont.Color = clWindowText
      FooterFont.Height = -12
      FooterFont.Name = 'MS Sans Serif'
      FooterFont.Style = []
      FooterRowCount = 1
      HorzScrollBar.Visible = False
      IndicatorOptions = [gioShowRowIndicatorEh]
      Options = [dgTitles, dgIndicator, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
      OptionsEh = [dghFixed3D, dghHighlightFocus, dghClearSelection, dghIncSearch, dghPreferIncSearch, dghDialogFind, dghColumnResize, dghExtendVertLines]
      ParentCtl3D = False
      PopupMenu = pmChamp
      ReadOnly = True
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -12
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      UseMultiTitle = True
      VertScrollBar.VisibleMode = sbNeverShowEh
      OnDblClick = actAddExecute
      OnEnter = dbgChampMatchEnter
      OnGetCellParams = dbgGetCellParams
      Columns = <
        item
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'NUMBER'
          Footers = <>
          Title.Caption = #8470
          Width = 23
        end
        item
          EditButtons = <>
          FieldName = 'NAME'
          Footer.Value = #1047#1072#1084#1077#1085#1099':'
          Footer.ValueType = fvtStaticText
          Footers = <>
          Title.Caption = #1048#1075#1088#1086#1082#1080'|'#1048#1084#1103
          Width = 27
        end
        item
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'PLAYER_TYPE'
          Footers = <>
          Title.Caption = #1048#1075#1088#1086#1082#1080'|'#1040#1084#1087#1083#1091#1072
          Width = 105
        end
        item
          Alignment = taCenter
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'GOAL_COUNT'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          Footers = <>
          Title.Caption = #1043#1086#1083#1099'|'#1050#1086#1083'-'#1074#1086
          Width = 52
        end
        item
          Alignment = taCenter
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'GOAL_MINUTE'
          Footers = <>
          Title.Caption = #1043#1086#1083#1099'|'#1052#1080#1085#1091#1090#1072
          Width = 52
        end>
      object RowDetailData: TRowDetailPanelControlEh
      end
    end
    object dbgMatch1: TDBGridEh
      Left = 285
      Top = 16
      Width = 568
      Height = 181
      Align = alClient
      AllowedOperations = []
      Ctl3D = False
      DataGrouping.GroupLevels = <>
      DataSource = dsrcMatch1
      Flat = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      FooterColor = clBtnFace
      FooterFont.Charset = DEFAULT_CHARSET
      FooterFont.Color = clWindowText
      FooterFont.Height = -12
      FooterFont.Name = 'MS Sans Serif'
      FooterFont.Style = []
      FooterRowCount = 1
      HorzScrollBar.Visible = False
      IndicatorOptions = [gioShowRowIndicatorEh]
      Options = [dgTitles, dgIndicator, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
      OptionsEh = [dghFixed3D, dghHighlightFocus, dghClearSelection, dghIncSearch, dghPreferIncSearch, dghDialogFind, dghColumnResize, dghExtendVertLines]
      ParentCtl3D = False
      ParentFont = False
      PopupMenu = pmMatch
      ReadOnly = True
      SumList.Active = True
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -12
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      UseMultiTitle = True
      VertScrollBar.VisibleMode = sbNeverShowEh
      OnEnter = dbgChampMatchEnter
      OnGetCellParams = dbgGetCellParams
      Columns = <
        item
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'NUMBER'
          Footer.FieldName = 'NUMBER'
          Footers = <>
          Title.Caption = #8470
          Width = 27
        end
        item
          EditButtons = <>
          FieldName = 'NAME'
          Footer.Alignment = taRightJustify
          Footer.FieldName = 'NUMBER'
          Footer.Font.Charset = DEFAULT_CHARSET
          Footer.Font.Color = clWindowText
          Footer.Font.Height = -11
          Footer.Font.Name = 'MS Sans Serif'
          Footer.Font.Style = []
          Footer.ValueType = fvtCount
          Footers = <>
          Title.Caption = #1048#1075#1088#1086#1082#1080'|'#1048#1084#1103
          Width = 86
        end
        item
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'PLAYER_TYPE'
          Footers = <>
          Title.Caption = #1048#1075#1088#1086#1082#1080'|'#1040#1084#1087#1083#1091#1072
          Width = 106
        end
        item
          Alignment = taCenter
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'GOAL_COUNT'
          Footers = <>
          Title.Caption = #1043#1086#1083#1099'|'#1050#1086#1083'-'#1074#1086
          Width = 52
        end
        item
          Alignment = taCenter
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'GOAL_MINUTE'
          Footers = <>
          Title.Caption = #1043#1086#1083#1099'|'#1052#1080#1085#1091#1090#1072
          Width = 52
        end>
      object RowDetailData: TRowDetailPanelControlEh
      end
    end
    object pnlBottom1: TPanel
      Left = 2
      Top = 197
      Width = 858
      Height = 7
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 2
    end
    object pnlLeft1: TPanel
      Left = 2
      Top = 16
      Width = 6
      Height = 181
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 3
    end
    object pnlMiddle1: TPanel
      Left = 279
      Top = 16
      Width = 6
      Height = 181
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 4
    end
    object pnlRight1: TPanel
      Left = 853
      Top = 16
      Width = 7
      Height = 181
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 5
    end
    object pnlTop1: TPanel
      Left = 2
      Top = 15
      Width = 858
      Height = 1
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 6
    end
  end
  object pnlMiddle: TPanel
    Left = 0
    Top = 209
    Width = 862
    Height = 6
    Align = alTop
    BevelOuter = bvNone
    Ctl3D = True
    ParentCtl3D = False
    TabOrder = 2
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 862
    Height = 3
    Align = alTop
    BevelOuter = bvNone
    Ctl3D = True
    ParentCtl3D = False
    TabOrder = 3
  end
  object alMain: TActionList
    Left = 820
    Top = 8
    object actClose: TAction
      Caption = 'actClose'
      ShortCut = 8219
      OnExecute = actCloseExecute
    end
    object actLoad: TAction
      Caption = 'actLoad'
      ShortCut = 116
      OnExecute = actLoadExecute
    end
    object actAdd: TAction
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1074' '#1089#1090#1072#1088#1090#1086#1074#1099#1081' '#1089#1086#1089#1090#1072#1074
      ShortCut = 16397
      OnExecute = actAddExecute
    end
    object actGetInfo: TAction
      Caption = 'actGetInfo'
      OnExecute = actGetInfoExecute
    end
    object actSubst: TAction
      Caption = #1047#1072#1084#1077#1085#1072
      OnExecute = actSubstExecute
    end
    object actDel: TAction
      Caption = #1059#1073#1088#1072#1090#1100' '#1080#1075#1088#1086#1082#1072' '#1080#1079' '#1089#1086#1089#1090#1072#1074#1072
      ShortCut = 16430
      OnExecute = actDelExecute
    end
  end
  object dsrcChamp1: TDataSource
    DataSet = dsChamp1
    Left = 4
    Top = 44
  end
  object dsChamp1: TClientDataSet
    Aggregates = <>
    IndexFieldNames = 'ORD_NUM'
    Params = <>
    ProviderName = 'dspData'
    Left = 32
    Top = 44
  end
  object dsrcChamp2: TDataSource
    DataSet = dsChamp2
    Left = 4
    Top = 336
  end
  object dsChamp2: TClientDataSet
    Tag = 1
    Aggregates = <>
    IndexFieldNames = 'ORD_NUM'
    Params = <>
    ProviderName = 'dspData'
    Left = 32
    Top = 336
  end
  object dsrcMatch1: TDataSource
    DataSet = dsMatch1
    Left = 392
    Top = 44
  end
  object dsMatch1: TClientDataSet
    Aggregates = <>
    IndexFieldNames = 'ORD_NUM'
    Params = <>
    ProviderName = 'dspData'
    Left = 420
    Top = 44
  end
  object dsrcMatch2: TDataSource
    DataSet = dsMatch2
    Left = 392
    Top = 336
  end
  object dsMatch2: TClientDataSet
    Tag = 1
    Aggregates = <>
    IndexFieldNames = 'ORD_NUM'
    Params = <>
    ProviderName = 'dspData'
    Left = 420
    Top = 336
  end
  object dsData: TClientDataSet
    Aggregates = <>
    Params = <>
    Left = 216
    Top = 48
  end
  object dspData: TDataSetProvider
    DataSet = dsData
    Constraints = True
    OnDataRequest = dspDataDataRequest
    Left = 216
    Top = 92
  end
  object pmChamp: TPopupMenu
    Left = 4
    Top = 72
    object pmChamp1N1: TMenuItem
      Action = actAdd
    end
    object miCardChamp: TMenuItem
      Caption = #1050#1072#1088#1090#1086#1095#1082#1072
    end
    object N10: TMenuItem
      Action = actSubst
    end
  end
  object pmMatch: TPopupMenu
    Left = 392
    Top = 72
    object miGoal: TMenuItem
      Caption = #1043#1054#1054#1054#1054#1051'!!!!'
    end
    object miSubst: TMenuItem
      Action = actSubst
    end
    object miCardMatch: TMenuItem
      Caption = #1050#1072#1088#1090#1086#1095#1082#1072
    end
    object N4: TMenuItem
      Caption = '-'
    end
    object N6: TMenuItem
      Action = actDel
    end
  end
end
