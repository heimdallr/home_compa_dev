object fmPlayer: TfmPlayer
  Left = 1027
  Top = 117
  Width = 870
  Height = 640
  Caption = 'fmPlayer'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poMainFormCenter
  Visible = True
  WindowState = wsMaximized
  OnClose = FormClose
  OnResize = FormResize
  PixelsPerInch = 120
  TextHeight = 16
  object pnlPlayer2: TGroupBox
    Left = 0
    Top = 265
    Width = 862
    Height = 343
    Align = alClient
    Caption = 'pnlPlayer2'
    TabOrder = 1
    object dbgChamp2: TDBGridEh
      Tag = 1
      Left = 10
      Top = 19
      Width = 335
      Height = 314
      Align = alLeft
      AllowedOperations = []
      Ctl3D = False
      DataGrouping.GroupLevels = <>
      DataSource = dsrcChamp2
      Flat = True
      FooterColor = clBtnFace
      FooterFont.Charset = DEFAULT_CHARSET
      FooterFont.Color = clWindowText
      FooterFont.Height = -13
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
      TitleFont.Height = -13
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
          Width = 25
        end
        item
          EditButtons = <>
          FieldName = 'NAME'
          Footer.Value = #1047#1072#1084#1077#1085#1099':'
          Footer.ValueType = fvtStaticText
          Footers = <>
          Title.Caption = #1048#1075#1088#1086#1082#1080'|'#1048#1084#1103
          Width = 48
        end
        item
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'PLAYER_TYPE'
          Footers = <>
          Title.Caption = #1048#1075#1088#1086#1082#1080'|'#1040#1084#1087#1083#1091#1072
          Width = 129
        end
        item
          Alignment = taCenter
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'GOAL_COUNT'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          Footers = <>
          Title.Caption = #1043#1086#1083#1099'|'#1050#1086#1083'-'#1074#1086
        end
        item
          Alignment = taCenter
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'GOAL_MINUTE'
          Footers = <>
          Title.Caption = #1043#1086#1083#1099'|'#1052#1080#1085#1091#1090#1072
        end>
      object RowDetailData: TRowDetailPanelControlEh
      end
    end
    object dbgMatch2: TDBGridEh
      Tag = 1
      Left = 353
      Top = 19
      Width = 499
      Height = 314
      Align = alClient
      AllowedOperations = []
      Ctl3D = False
      DataGrouping.GroupLevels = <>
      DataSource = dsrcMatch2
      Flat = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      FooterColor = clBtnFace
      FooterFont.Charset = DEFAULT_CHARSET
      FooterFont.Color = clWindowText
      FooterFont.Height = -15
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
      TitleFont.Height = -15
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
          Width = 33
        end
        item
          EditButtons = <>
          FieldName = 'NAME'
          Footer.Alignment = taRightJustify
          Footer.FieldName = 'NUMBER'
          Footer.ValueType = fvtCount
          Footers = <>
          Title.Caption = #1048#1075#1088#1086#1082#1080'|'#1048#1084#1103
          Width = 105
        end
        item
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'PLAYER_TYPE'
          Footers = <>
          Title.Caption = #1048#1075#1088#1086#1082#1080'|'#1040#1084#1087#1083#1091#1072
          Width = 130
        end
        item
          Alignment = taCenter
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'GOAL_COUNT'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          Footers = <>
          Title.Caption = #1043#1086#1083#1099'|'#1050#1086#1083'-'#1074#1086
        end
        item
          Alignment = taCenter
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'GOAL_MINUTE'
          Footers = <>
          Title.Caption = #1043#1086#1083#1099'|'#1052#1080#1085#1091#1090#1072
        end>
      object RowDetailData: TRowDetailPanelControlEh
      end
    end
    object pnlBottom2: TPanel
      Left = 2
      Top = 333
      Width = 858
      Height = 8
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 2
    end
    object pnlLeft2: TPanel
      Left = 2
      Top = 19
      Width = 8
      Height = 314
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 3
    end
    object pnlMiddle2: TPanel
      Left = 345
      Top = 19
      Width = 8
      Height = 314
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 4
    end
    object pnlRight2: TPanel
      Left = 852
      Top = 19
      Width = 8
      Height = 314
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 5
    end
    object pnlTop2: TPanel
      Left = 2
      Top = 18
      Width = 858
      Height = 1
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 6
    end
  end
  object pnlPlayer1: TGroupBox
    Left = 0
    Top = 4
    Width = 862
    Height = 253
    Align = alTop
    Caption = 'pnlPlayer1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object dbgChamp1: TDBGridEh
      Left = 10
      Top = 19
      Width = 333
      Height = 223
      Align = alLeft
      AllowedOperations = []
      Ctl3D = False
      DataGrouping.GroupLevels = <>
      DataSource = dsrcChamp1
      Flat = True
      FooterColor = clBtnFace
      FooterFont.Charset = DEFAULT_CHARSET
      FooterFont.Color = clWindowText
      FooterFont.Height = -15
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
      TitleFont.Height = -15
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
          Width = 28
        end
        item
          EditButtons = <>
          FieldName = 'NAME'
          Footer.Value = #1047#1072#1084#1077#1085#1099':'
          Footer.ValueType = fvtStaticText
          Footers = <>
          Title.Caption = #1048#1075#1088#1086#1082#1080'|'#1048#1084#1103
          Width = 34
        end
        item
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'PLAYER_TYPE'
          Footers = <>
          Title.Caption = #1048#1075#1088#1086#1082#1080'|'#1040#1084#1087#1083#1091#1072
          Width = 129
        end
        item
          Alignment = taCenter
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'GOAL_COUNT'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          Footers = <>
          Title.Caption = #1043#1086#1083#1099'|'#1050#1086#1083'-'#1074#1086
        end
        item
          Alignment = taCenter
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'GOAL_MINUTE'
          Footers = <>
          Title.Caption = #1043#1086#1083#1099'|'#1052#1080#1085#1091#1090#1072
        end>
      object RowDetailData: TRowDetailPanelControlEh
      end
    end
    object dbgMatch1: TDBGridEh
      Left = 351
      Top = 19
      Width = 501
      Height = 223
      Align = alClient
      AllowedOperations = []
      Ctl3D = False
      DataGrouping.GroupLevels = <>
      DataSource = dsrcMatch1
      Flat = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      FooterColor = clBtnFace
      FooterFont.Charset = DEFAULT_CHARSET
      FooterFont.Color = clWindowText
      FooterFont.Height = -15
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
      TitleFont.Height = -15
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
          Width = 33
        end
        item
          EditButtons = <>
          FieldName = 'NAME'
          Footer.Alignment = taRightJustify
          Footer.FieldName = 'NUMBER'
          Footer.Font.Charset = DEFAULT_CHARSET
          Footer.Font.Color = clWindowText
          Footer.Font.Height = -15
          Footer.Font.Name = 'MS Sans Serif'
          Footer.Font.Style = []
          Footer.ValueType = fvtCount
          Footers = <>
          Title.Caption = #1048#1075#1088#1086#1082#1080'|'#1048#1084#1103
          Width = 106
        end
        item
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'PLAYER_TYPE'
          Footers = <>
          Title.Caption = #1048#1075#1088#1086#1082#1080'|'#1040#1084#1087#1083#1091#1072
          Width = 131
        end
        item
          Alignment = taCenter
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'GOAL_COUNT'
          Footers = <>
          Title.Caption = #1043#1086#1083#1099'|'#1050#1086#1083'-'#1074#1086
        end
        item
          Alignment = taCenter
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'GOAL_MINUTE'
          Footers = <>
          Title.Caption = #1043#1086#1083#1099'|'#1052#1080#1085#1091#1090#1072
        end>
      object RowDetailData: TRowDetailPanelControlEh
      end
    end
    object pnlBottom1: TPanel
      Left = 2
      Top = 242
      Width = 858
      Height = 9
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 2
    end
    object pnlLeft1: TPanel
      Left = 2
      Top = 19
      Width = 8
      Height = 223
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 3
    end
    object pnlMiddle1: TPanel
      Left = 343
      Top = 19
      Width = 8
      Height = 223
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 4
    end
    object pnlRight1: TPanel
      Left = 852
      Top = 19
      Width = 8
      Height = 223
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 5
    end
    object pnlTop1: TPanel
      Left = 2
      Top = 18
      Width = 858
      Height = 1
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 6
    end
  end
  object pnlMiddle: TPanel
    Left = 0
    Top = 257
    Width = 862
    Height = 8
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
    Height = 4
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
