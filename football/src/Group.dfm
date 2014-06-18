object fmGroup: TfmGroup
  Left = 361
  Top = 152
  Width = 870
  Height = 640
  Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090#1099' '#1075#1088#1091#1087#1087#1086#1074#1086#1075#1086' '#1090#1091#1088#1085#1080#1088#1072
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
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
  PixelsPerInch = 120
  TextHeight = 16
  object dbgData: TDBGridEh
    Left = 0
    Top = 0
    Width = 862
    Height = 608
    Align = alClient
    AllowedOperations = []
    AutoFitColWidths = True
    ColumnDefValues.Title.Alignment = taCenter
    Ctl3D = False
    DataGrouping.GroupLevels = <>
    DataSource = dsrcData
    DefaultDrawing = False
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    FooterColor = clWindow
    FooterFont.Charset = DEFAULT_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -15
    FooterFont.Name = 'MS Sans Serif'
    FooterFont.Style = []
    IndicatorOptions = []
    Options = [dgEditing, dgTitles, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
    ParentCtl3D = False
    ParentFont = False
    PopupMenu = pmMain
    ReadOnly = True
    RowHeight = 30
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -20
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    VertScrollBar.VisibleMode = sbNeverShowEh
    OnDrawColumnCell = dbgDataDrawColumnCell
    Columns = <
      item
        Alignment = taCenter
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'Group'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -20
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        Footers = <>
        HideDuplicates = True
        Title.Caption = ' '
        Width = 42
      end
      item
        Alignment = taCenter
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'Num'
        Footers = <>
        Title.Caption = #8470
        Width = 40
      end
      item
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'Id'
        Footers = <>
        ImageList = ilFlag
        Title.Caption = #1060#1083#1072#1075
        Width = 45
      end
      item
        Alignment = taCenter
        EditButtons = <>
        FieldName = 'Country'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -20
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        Footers = <>
        Title.Caption = #1057#1073#1086#1088#1085#1072#1103
        Width = 131
      end
      item
        Alignment = taCenter
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'Game'
        Footers = <>
        Title.Caption = #1048
        Width = 28
      end
      item
        Alignment = taCenter
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'Win'
        Footers = <>
        Title.Caption = #1042
        Width = 24
      end
      item
        Alignment = taCenter
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'Deuce'
        Footers = <>
        Title.Caption = #1053
        Width = 22
      end
      item
        Alignment = taCenter
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'Lose'
        Footers = <>
        Title.Caption = #1055
        Width = 24
      end
      item
        Alignment = taCenter
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'Goal'
        Footers = <>
        Title.Caption = #1052#1103#1095#1080
        Width = 46
      end
      item
        Alignment = taCenter
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'Point'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -20
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        Footers = <>
        Title.Caption = #1054
        Width = 25
      end
      item
        Alignment = taCenter
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'Place'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -20
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        Footers = <>
        Title.Caption = #1052
        Width = 46
      end>
    object RowDetailData: TRowDetailPanelControlEh
    end
  end
  object ActionList1: TActionList
    Left = 824
    Top = 4
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
    object actDelPlace: TAction
      Caption = #1057#1085#1103#1090#1100' '#1084#1077#1089#1090#1086
      ShortCut = 32816
      OnExecute = actSetPlaceExecute
    end
  end
  object dsrcData: TDataSource
    DataSet = dsData
    Left = 12
    Top = 16
  end
  object dsData: TClientDataSet
    Aggregates = <>
    Params = <>
    AfterScroll = dsDataAfterScroll
    Left = 40
    Top = 16
  end
  object pmMain: TPopupMenu
    Left = 60
    Top = 92
    object N1: TMenuItem
      Action = actDelPlace
    end
  end
  object ilFlag: TImageList
    Height = 30
    Width = 45
    Left = 112
    Top = 184
  end
end
