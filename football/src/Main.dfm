object fmMain: TfmMain
  Left = 255
  Top = 117
  Width = 873
  Height = 659
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  Caption = 'fmMain'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  WindowState = wsMaximized
  OnClose = FormClose
  OnDestroy = FormDestroy
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object dbgData: TDBGridEh
    Left = 0
    Top = 0
    Width = 865
    Height = 629
    Align = alClient
    AllowedOperations = [alopUpdateEh]
    AutoFitColWidths = True
    ColumnDefValues.Title.Alignment = taCenter
    Ctl3D = False
    DataGrouping.GroupLevels = <>
    DataSource = dsrcData
    Flat = True
    FooterColor = clWindow
    FooterFont.Charset = DEFAULT_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -10
    FooterFont.Name = 'MS Sans Serif'
    FooterFont.Style = []
    IndicatorOptions = []
    Options = [dgTitles, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentCtl3D = False
    PopupMenu = pmMain
    ReadOnly = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -10
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    VertScrollBar.VisibleMode = sbNeverShowEh
    OnDblClick = actOpenExecute
    OnGetCellParams = dbgDataGetCellParams
    OnMouseDown = dbgDataMouseDown
    OnMouseUp = dbgDataMouseUp
    Columns = <
      item
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'ORD_NUM'
        Footers = <>
        Title.Caption = #8470
        Width = 44
      end
      item
        EditButtons = <>
        FieldName = 'CITY_NAME'
        Footers = <>
        Title.Caption = #1043#1086#1088#1086#1076
      end
      item
        AutoFitColWidth = False
        DisplayFormat = 'dd.mm hh:nn'
        EditButtons = <>
        FieldName = 'PLAY_AT'
        Footers = <>
        Title.Caption = #1053#1072#1095#1072#1083#1086
        Width = 104
      end
      item
        Alignment = taCenter
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'STATUS'
        Footers = <>
        HideDuplicates = True
        Title.Caption = #1069#1090#1072#1087
        Width = 104
      end
      item
        Alignment = taCenter
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'GROUP_NAME'
        Footers = <>
        HideDuplicates = True
        Title.Caption = #1043#1088#1091#1087#1087#1072
        Width = 61
      end
      item
        Alignment = taCenter
        EditButtons = <>
        FieldName = 'COUNTRIES'
        Footers = <>
        Title.Caption = #1059#1095#1072#1089#1090#1085#1080#1082#1080' '#1084#1072#1090#1095#1072
        Width = 151
      end
      item
        Alignment = taCenter
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'GOAL_COUNT'
        Footers = <>
        Title.Caption = #1057#1095#1077#1090
        Width = 104
      end>
    object RowDetailData: TRowDetailPanelControlEh
    end
  end
  object alMain: TActionList
    Left = 676
    Top = 12
    object actLoad: TAction
      Caption = 'actLoad'
      ShortCut = 116
      OnExecute = actLoadExecute
    end
    object actOpen: TAction
      Caption = #1044#1077#1090#1072#1083#1080#1079#1072#1094#1080#1103' '#1084#1072#1090#1095#1072
      ShortCut = 16397
      OnExecute = actOpenExecute
    end
    object actReady: TAction
      Caption = #1057#1084#1077#1085#1080#1090#1100' '#1087#1088#1080#1079#1085#1072#1082' '#1086#1082#1086#1085#1095#1072#1085#1080#1103' '#1084#1072#1090#1095#1072
      ShortCut = 113
      OnExecute = actReadyExecute
    end
    object actSetCountry1: TAction
      Caption = #1071#1074#1085#1086
      ShortCut = 32817
      OnExecute = actSetCountryExecute
    end
    object actSetCountry2: TAction
      Tag = 1
      Caption = #1071#1074#1085#1086
      ShortCut = 32818
      OnExecute = actSetCountryExecute
    end
    object actSetCountry1ByGroup: TAction
      Caption = #1055#1086' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1072#1084' '#1080#1075#1088' '#1074' '#1087#1086#1076#1075#1088#1091#1087#1087#1072#1093
      ShortCut = 24625
      OnExecute = actSetCountryByGroupExecute
    end
    object actSetCountry2ByGroup: TAction
      Tag = 1
      Caption = #1055#1086' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1072#1084' '#1080#1075#1088' '#1074' '#1087#1086#1076#1075#1088#1091#1087#1087#1072#1093
      ShortCut = 24626
      OnExecute = actSetCountryByGroupExecute
    end
    object actGroup: TAction
      Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090#1099' '#1075#1088#1091#1087#1087#1086#1074#1086#1075#1086' '#1090#1091#1088#1085#1080#1088#1072
      ShortCut = 32839
      OnExecute = actGroupExecute
    end
  end
  object dsrcData: TDataSource
    DataSet = dsData
    Left = 8
    Top = 40
  end
  object dsData: TClientDataSet
    Aggregates = <>
    IndexFieldNames = 'ord_num'
    Params = <>
    AfterScroll = dsDataAfterScroll
    Left = 40
    Top = 40
  end
  object pmMain: TPopupMenu
    Left = 96
    Top = 48
    object N1: TMenuItem
      Action = actOpen
    end
    object N2: TMenuItem
      Action = actReady
    end
    object N3: TMenuItem
      Caption = '-'
    end
    object N11: TMenuItem
      Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1091#1095#1072#1089#1090#1085#1080#1082#1072' '#8470'1'
      object N12: TMenuItem
        Action = actSetCountry1
      end
      object N4: TMenuItem
        Action = actSetCountry1ByGroup
      end
    end
    object N21: TMenuItem
      Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1091#1095#1072#1089#1090#1085#1080#1082#1072' '#8470'2'
      object N22: TMenuItem
        Action = actSetCountry2
      end
      object N5: TMenuItem
        Action = actSetCountry2ByGroup
      end
    end
  end
end
