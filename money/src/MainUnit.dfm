object fmMain: TfmMain
  Left = 366
  Top = 44
  Width = 1305
  Height = 750
  Caption = 'fmMain'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = mmMain
  OldCreateOrder = False
  OnActivate = FormActivate
  OnDestroy = FormDestroy
  OnDeactivate = FormDeactivate
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object splMain: TSplitter
    Left = 911
    Top = 29
    Width = 4
    Height = 669
    Cursor = crHSplit
    Align = alRight
  end
  object pnlRight: TPanel
    Left = 915
    Top = 29
    Width = 382
    Height = 669
    Align = alRight
    BevelOuter = bvNone
    TabOrder = 1
    object dbgStock: TDBGridEh
      Left = 0
      Top = 0
      Width = 382
      Height = 669
      Align = alClient
      AllowedOperations = []
      AutoFitColWidths = True
      ColumnDefValues.Title.Alignment = taCenter
      ColumnDefValues.Title.TitleButton = True
      Ctl3D = False
      DataGrouping.GroupLevels = <>
      DataSource = dsrcStock
      Flat = True
      FooterColor = 11579568
      FooterFont.Charset = DEFAULT_CHARSET
      FooterFont.Color = clWindowText
      FooterFont.Height = -10
      FooterFont.Name = 'MS Sans Serif'
      FooterFont.Style = []
      FooterRowCount = 1
      IndicatorOptions = [gioShowRowIndicatorEh]
      OddRowColor = 15790320
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentCtl3D = False
      PopupMenu = pmStock
      ReadOnly = True
      SumList.Active = True
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -10
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      OnGetCellParams = dbgStockGetCellParams
      OnGetFooterParams = dbgGetFooterParams
      Columns = <
        item
          EditButtons = <>
          FieldName = 'NAME'
          Footer.Value = #1048#1090#1086#1075#1086':'
          Footer.ValueType = fvtStaticText
          Footers = <>
          Title.Caption = #1057#1095#1077#1090
          Width = 111
        end
        item
          AutoFitColWidth = False
          DisplayFormat = '# ### ##0.00'
          EditButtons = <>
          FieldName = 'SUMMA'
          Footer.DisplayFormat = '# ### ##0.00'
          Footer.FieldName = 'SUMMA'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Caption = #1041#1072#1083#1072#1085#1089
          Width = 114
        end>
      object RowDetailData: TRowDetailPanelControlEh
      end
    end
  end
  object pnlMain: TPanel
    Left = 0
    Top = 29
    Width = 911
    Height = 669
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object pnlDoc: TPanel
      Left = 0
      Top = 0
      Width = 911
      Height = 669
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 0
      object dbgDoc: TDBGridEh
        Left = 0
        Top = 0
        Width = 911
        Height = 669
        Align = alClient
        AllowedOperations = []
        AutoFitColWidths = True
        ColumnDefValues.Title.Alignment = taCenter
        ColumnDefValues.Title.TitleButton = True
        Ctl3D = False
        DataGrouping.GroupLevels = <>
        DataSource = dsrcDoc
        EvenRowColor = clWindow
        Flat = True
        FooterColor = 11579568
        FooterFont.Charset = DEFAULT_CHARSET
        FooterFont.Color = clWindowText
        FooterFont.Height = -10
        FooterFont.Name = 'MS Sans Serif'
        FooterFont.Style = []
        FooterRowCount = 1
        IndicatorOptions = [gioShowRowIndicatorEh]
        OddRowColor = 15790320
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        ParentCtl3D = False
        PopupMenu = pmDoc
        ReadOnly = True
        RowDetailPanel.Active = True
        RowDetailPanel.Height = 210
        RowDetailPanel.ActiveControl = dbgStr
        RowDetailPanel.BevelInner = bvNone
        RowDetailPanel.BevelOuter = bvNone
        RowDetailPanel.BorderStyle = bsNone
        SumList.Active = True
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -10
        TitleFont.Name = 'MS Sans Serif'
        TitleFont.Style = []
        OnGetFooterParams = dbgGetFooterParams
        OnRowDetailPanelShow = dbgDocRowDetailPanelShow
        OnTitleBtnClick = dbgDocTitleBtnClick
        Columns = <
          item
            AutoFitColWidth = False
            Checkboxes = True
            EditButtons = <>
            FieldName = 'STATE'
            Footer.FieldName = 'STATE'
            Footer.ValueType = fvtSum
            Footers = <>
            KeyList.Strings = (
              '1'
              '0')
            PickList.Strings = (
              '1'
              '0')
            Title.Caption = ' '
            Width = 21
          end
          item
            AutoFitColWidth = False
            EditButtons = <>
            FieldName = 'ID'
            Footer.FieldName = 'ID'
            Footer.ValueType = fvtCount
            Footers = <>
            Title.Caption = #1053#1086#1084#1077#1088
            Width = 72
          end
          item
            AutoFitColWidth = False
            EditButtons = <>
            FieldName = 'DATE_DOC'
            Footers = <>
            Title.Caption = #1044#1072#1090#1072
            Width = 78
          end
          item
            EditButtons = <>
            FieldName = 'DOC_TYPE_NAME'
            Footers = <>
            Title.Caption = #1054#1087#1077#1088#1072#1094#1080#1103
            Width = 139
          end
          item
            EditButtons = <>
            FieldName = 'DEPOSIT_NAME'
            Footers = <>
            Title.Caption = #1057#1095#1077#1090
            Width = 239
          end
          item
            AutoFitColWidth = False
            DisplayFormat = '# ### ##0.00'
            EditButtons = <>
            FieldName = 'SUMMA'
            Footer.DisplayFormat = '# ### ##0.00'
            Footer.FieldName = 'SUMMA'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #1057#1091#1084#1084#1072
            Width = 75
          end
          item
            EditButtons = <>
            FieldName = 'NOTE'
            Footers = <>
            Title.Caption = #1055#1088#1080#1084#1077#1095#1072#1085#1080#1077
            Width = 285
          end>
        object RowDetailData: TRowDetailPanelControlEh
          object dbgStr: TDBGridEh
            Left = 0
            Top = 0
            Width = 878
            Height = 210
            Align = alClient
            AllowedOperations = []
            AutoFitColWidths = True
            ColumnDefValues.Title.Alignment = taCenter
            Ctl3D = False
            DataGrouping.GroupLevels = <>
            DataSource = dsrcStr
            Flat = True
            FooterColor = 11579568
            FooterFont.Charset = DEFAULT_CHARSET
            FooterFont.Color = clWindowText
            FooterFont.Height = -10
            FooterFont.Name = 'MS Sans Serif'
            FooterFont.Style = []
            FooterRowCount = 1
            IndicatorOptions = [gioShowRowIndicatorEh]
            OddRowColor = 15790320
            Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
            ParentCtl3D = False
            PopupMenu = pmStr
            RowDetailPanel.Height = 100
            SumList.Active = True
            TabOrder = 0
            TitleFont.Charset = DEFAULT_CHARSET
            TitleFont.Color = clWindowText
            TitleFont.Height = -10
            TitleFont.Name = 'MS Sans Serif'
            TitleFont.Style = []
            VertScrollBar.VisibleMode = sbNeverShowEh
            OnTitleBtnClick = dbgStrTitleBtnClick
            Columns = <
              item
                EditButtons = <>
                FieldName = 'TARGET_PERSON_NAME'
                Footers = <>
                Title.Caption = #1042#1080#1085#1086#1074#1085#1080#1082
                Width = 82
              end
              item
                EditButtons = <>
                FieldName = 'STR_TYPE_NAME'
                Footer.Alignment = taRightJustify
                Footer.FieldName = 'STR_TYPE_NAME'
                Footer.ValueType = fvtCount
                Footers = <>
                Title.Caption = #1058#1080#1087' '#1087#1083#1072#1090#1077#1078#1072
                Width = 180
              end
              item
                DisplayFormat = '# ### ##0.00'
                EditButtons = <>
                FieldName = 'SUMMA'
                Footer.DisplayFormat = '# ### ##0.00'
                Footer.FieldName = 'SUMMA'
                Footer.ValueType = fvtSum
                Footers = <>
                Title.Caption = #1057#1091#1084#1084#1072
                Width = 94
              end
              item
                EditButtons = <>
                FieldName = 'QTY'
                Footers = <>
                Title.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086
                Width = 79
              end
              item
                EditButtons = <>
                FieldName = 'NOTE'
                Footers = <>
                Title.Caption = #1055#1088#1080#1084#1077#1095#1072#1085#1080#1077
                Width = 399
              end>
            object RowDetailData: TRowDetailPanelControlEh
            end
          end
        end
      end
    end
  end
  object pnlFilter: TPanel
    Left = 0
    Top = 0
    Width = 1297
    Height = 29
    Align = alTop
    TabOrder = 2
    object lDateInterval: TLabel
      Left = 12
      Top = 8
      Width = 60
      Height = 13
      Cursor = crHandPoint
      Caption = 'lDateInterval'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -10
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      OnClick = lDateIntervalClick
      OnMouseEnter = lDateIntervalMouseEnter
      OnMouseLeave = lDateIntervalMouseLeave
    end
  end
  object mmMain: TMainMenu
    Left = 348
    Top = 300
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083
      object N3: TMenuItem
        Action = actExit
      end
    end
    object N5: TMenuItem
      Caption = #1044#1072#1085#1085#1099#1077
      object actAccept1: TMenuItem
        Action = actAccept
      end
      object actDelDoc1: TMenuItem
        Action = actDelDoc
      end
      object N7: TMenuItem
        Caption = '-'
      end
      object N8: TMenuItem
        Action = actAddStr
      end
      object N6: TMenuItem
        Action = actEditStr
      end
      object N15: TMenuItem
        Action = actDelStr
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object N2: TMenuItem
        Action = actShowCatalog
      end
    end
    object mmReport: TMenuItem
      Caption = #1054#1090#1095#1077#1090#1099
    end
    object N13: TMenuItem
      Caption = #1057#1087#1088#1072#1074#1082#1072
      object N14: TMenuItem
        Action = actAbout
      end
    end
  end
  object alMain: TActionList
    Left = 372
    Top = 300
    object actExit: TAction
      Caption = #1042#1099#1093#1086#1076
      ShortCut = 32856
      OnExecute = actExitExecute
    end
    object actLoad: TAction
      Caption = #1054#1073#1085#1086#1074#1080#1090#1100
      ShortCut = 116
      OnExecute = actLoadExecute
    end
    object actChangeDateInterval: TAction
      Caption = #1048#1085#1090#1077#1088#1074#1072#1083' '#1076#1072#1090
      OnExecute = actChangeDateIntervalExecute
    end
    object actAddStr: TAction
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1089#1090#1088#1086#1082#1091' '#1074' '#1076#1086#1082#1091#1084#1077#1085#1090'...'
      ShortCut = 32846
      OnExecute = actAddStrExecute
    end
    object actAccept: TAction
      Caption = #1055#1088#1086#1074#1086#1076#1082#1072' '#1076#1086#1082#1091#1084#1077#1085#1090#1072
      ShortCut = 113
      OnExecute = actAcceptExecute
    end
    object actDelDoc: TAction
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1076#1086#1082#1091#1084#1077#1085#1090
      ShortCut = 16430
      OnExecute = actDelDocExecute
    end
    object actEditStr: TAction
      Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100' '#1089#1090#1088#1086#1082#1091'...'
      ShortCut = 32781
      OnExecute = actEditStrExecute
    end
    object actDelStr: TAction
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1089#1090#1088#1086#1082#1091
      ShortCut = 32814
      OnExecute = actDelStrExecute
    end
    object actAbout: TAction
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077'...'
      OnExecute = actAboutExecute
    end
    object actShowCatalog: TAction
      Caption = #1054#1073#1097#1080#1081' '#1089#1087#1088#1072#1074#1086#1095#1085#1080#1082
      OnExecute = actShowCatalogExecute
    end
    object actLeft: TAction
      Caption = #1057#1074#1077#1088#1085#1091#1090#1100
      ShortCut = 37
      SecondaryShortCuts.Strings = (
        'Shift+Esc')
      OnExecute = actLeftExecute
    end
    object actRight: TAction
      Caption = 'actRight'
      ShortCut = 39
      OnExecute = actRightExecute
    end
    object actEditDoc: TAction
      Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100' '#1076#1086#1082#1091#1084#1077#1085#1090
      ShortCut = 16397
      OnExecute = actEditDocExecute
    end
    object actMul: TAction
      Caption = 'actMul'
      ShortCut = 16461
      OnExecute = actMulExecute
    end
  end
  object dsrcStock: TDataSource
    Left = 932
    Top = 64
  end
  object dsrcDoc: TDataSource
    Left = 16
    Top = 60
  end
  object dsrcStr: TDataSource
    Left = 16
    Top = 492
  end
  object pmDoc: TPopupMenu
    Left = 16
    Top = 88
    object actEditDoc1: TMenuItem
      Action = actEditDoc
    end
    object N9: TMenuItem
      Action = actAccept
    end
    object N16: TMenuItem
      Action = actDelDoc
    end
  end
  object pmStr: TPopupMenu
    Left = 16
    Top = 520
    object N10: TMenuItem
      Action = actAddStr
    end
    object N11: TMenuItem
      Action = actEditStr
    end
    object N12: TMenuItem
      Action = actDelStr
    end
  end
  object pmStock: TPopupMenu
    Left = 932
    Top = 92
  end
end
