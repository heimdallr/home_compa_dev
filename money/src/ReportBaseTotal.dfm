inherited fmReportBaseTotal: TfmReportBaseTotal
  Left = 579
  Top = 149
  Width = 786
  Height = 835
  Caption = 'fmReportBaseTotal'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited pnlFilter: TPanel
    Width = 778
    inherited pnlDateIntervalType: TPanel
      inherited lDateIntervalType: TLabel
        OnClick = nil
      end
    end
  end
  inherited pnlMain: TPanel
    Width = 778
    Height = 776
    object splOpt: TSplitter
      Left = 258
      Top = 1
      Width = 4
      Height = 774
      Cursor = crHSplit
    end
    object pnlOpts: TPanel
      Left = 1
      Top = 1
      Width = 257
      Height = 774
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 0
      object splPerson: TSplitter
        Left = 0
        Top = 529
        Width = 257
        Height = 4
        Cursor = crVSplit
        Align = alBottom
      end
      object dbgPerson: TDBGridEh
        Tag = 2
        Left = 0
        Top = 533
        Width = 257
        Height = 241
        Align = alBottom
        AllowedOperations = [alopUpdateEh]
        AutoFitColWidths = True
        Ctl3D = False
        DataGrouping.GroupLevels = <>
        DataSource = dsrcPerson
        Flat = True
        FooterColor = 11579568
        FooterFont.Charset = DEFAULT_CHARSET
        FooterFont.Color = clWindowText
        FooterFont.Height = -11
        FooterFont.Name = 'MS Sans Serif'
        FooterFont.Style = []
        FooterRowCount = 1
        IndicatorOptions = [gioShowRowIndicatorEh]
        OddRowColor = 15790320
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        ParentCtl3D = False
        SumList.Active = True
        TabOrder = 1
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'MS Sans Serif'
        TitleFont.Style = []
        UseMultiTitle = True
        VertScrollBar.VisibleMode = sbNeverShowEh
        OnMouseUp = dbgStateMouseUp
        Columns = <
          item
            EditButtons = <>
            FieldName = 'NAME'
            Footer.FieldName = 'NAME'
            Footer.ValueType = fvtCount
            Footers = <>
            ReadOnly = True
            Title.Caption = #1053#1072#1079#1085#1072#1095#1077#1085#1080#1077
            Width = 95
          end
          item
            AutoFitColWidth = False
            DisplayFormat = '# ### ### ##0.00'
            EditButtons = <>
            FieldName = 'SUMMA'
            Footer.DisplayFormat = '# ### ### ##0.00'
            Footer.FieldName = 'SUMMA'
            Footer.ValueType = fvtSum
            Footers = <>
            ReadOnly = True
            Title.Caption = #1057#1091#1084#1084#1072
          end
          item
            AutoFitColWidth = False
            DisplayFormat = '##0.0'
            EditButtons = <>
            FieldName = 'SUMMA_PCT'
            Footers = <>
            Title.Caption = '% '#1086#1090' '#1086#1073#1097#1077#1075#1086' '#1086#1073#1086#1088#1086#1090#1072
          end
          item
            AutoFitColWidth = False
            Checkboxes = True
            EditButtons = <>
            FieldName = 'CHECKED'
            Footer.FieldName = 'CHECKED'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = ' '
            Width = 26
          end>
        object RowDetailData: TRowDetailPanelControlEh
        end
      end
      object pnlOptClient: TPanel
        Left = 0
        Top = 0
        Width = 257
        Height = 529
        Align = alClient
        BevelOuter = bvNone
        Caption = 'pnlOptClient'
        TabOrder = 0
        object splDeposit: TSplitter
          Left = 0
          Top = 352
          Width = 257
          Height = 4
          Cursor = crVSplit
          Align = alBottom
        end
        object dbgDeposit: TDBGridEh
          Tag = 2
          Left = 0
          Top = 356
          Width = 257
          Height = 173
          Align = alBottom
          AllowedOperations = [alopUpdateEh]
          AutoFitColWidths = True
          Ctl3D = False
          DataGrouping.GroupLevels = <>
          DataSource = dsrcDeposit
          Flat = True
          FooterColor = 11579568
          FooterFont.Charset = DEFAULT_CHARSET
          FooterFont.Color = clWindowText
          FooterFont.Height = -11
          FooterFont.Name = 'MS Sans Serif'
          FooterFont.Style = []
          FooterRowCount = 1
          IndicatorOptions = [gioShowRowIndicatorEh]
          OddRowColor = 15790320
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
          ParentCtl3D = False
          SumList.Active = True
          TabOrder = 1
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'MS Sans Serif'
          TitleFont.Style = []
          UseMultiTitle = True
          VertScrollBar.VisibleMode = sbNeverShowEh
          OnMouseUp = dbgStateMouseUp
          Columns = <
            item
              EditButtons = <>
              FieldName = 'NAME'
              Footer.FieldName = 'NAME'
              Footer.ValueType = fvtCount
              Footers = <>
              ReadOnly = True
              Title.Caption = #1057#1095#1077#1090
              Width = 79
            end
            item
              AutoFitColWidth = False
              DisplayFormat = '# ### ### ##0.00'
              EditButtons = <>
              FieldName = 'SUMMA'
              Footer.DisplayFormat = '# ### ### ##0.00'
              Footer.FieldName = 'SUMMA'
              Footer.ValueType = fvtSum
              Footers = <>
              ReadOnly = True
              Title.Caption = #1057#1091#1084#1084#1072
            end
            item
              AutoFitColWidth = False
              DisplayFormat = '##0.0'
              EditButtons = <>
              FieldName = 'SUMMA_PCT'
              Footers = <>
              Title.Caption = '% '#1086#1090' '#1086#1073#1097#1077#1075#1086' '#1086#1073#1086#1088#1086#1090#1072
            end
            item
              AutoFitColWidth = False
              Checkboxes = True
              EditButtons = <>
              FieldName = 'CHECKED'
              Footer.FieldName = 'CHECKED'
              Footer.ValueType = fvtSum
              Footers = <>
              Title.Caption = ' '
              Width = 27
            end>
          object RowDetailData: TRowDetailPanelControlEh
          end
        end
        object dbgState: TDBGridEh
          Tag = 1
          Left = 0
          Top = 0
          Width = 257
          Height = 352
          Align = alClient
          AllowedOperations = [alopUpdateEh]
          AutoFitColWidths = True
          Ctl3D = False
          DataGrouping.GroupLevels = <>
          DataSource = dsrcState
          Flat = True
          FooterColor = 11579568
          FooterFont.Charset = DEFAULT_CHARSET
          FooterFont.Color = clWindowText
          FooterFont.Height = -11
          FooterFont.Name = 'MS Sans Serif'
          FooterFont.Style = []
          IndicatorOptions = [gioShowRowIndicatorEh]
          OddRowColor = 15790320
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
          ParentCtl3D = False
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'MS Sans Serif'
          TitleFont.Style = []
          UseMultiTitle = True
          OnMouseUp = dbgStateMouseUp
          Columns = <
            item
              EditButtons = <>
              FieldName = 'NAME'
              Footers = <>
              ReadOnly = True
              Title.Caption = #1057#1090#1072#1090#1100#1103
              Width = 57
            end
            item
              AutoFitColWidth = False
              DisplayFormat = '# ### ### ##0.00'
              EditButtons = <>
              FieldName = 'SUMMA'
              Footers = <>
              Title.Caption = #1057#1091#1084#1084#1072
            end
            item
              AutoFitColWidth = False
              DisplayFormat = '##0.0'
              EditButtons = <>
              FieldName = 'SUMMA_PCT'
              Footers = <>
              Title.Caption = '% '#1086#1090' '#1086#1073#1097#1077#1075#1086' '#1086#1073#1086#1088#1086#1090#1072
            end
            item
              AutoFitColWidth = False
              Checkboxes = True
              EditButtons = <>
              FieldName = 'CHECKED'
              Footers = <>
              Title.Caption = ' '
              Width = 29
            end>
          object RowDetailData: TRowDetailPanelControlEh
          end
        end
      end
    end
    object pnlRes: TPanel
      Left = 262
      Top = 1
      Width = 515
      Height = 774
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
    end
  end
  inherited alMain: TActionList
    inherited actRunReport: TAction
      OnExecute = actRunReportExecute
    end
    object actLeft: TAction [3]
      Caption = 'actLeft'
      ShortCut = 37
      OnExecute = actLeftExecute
    end
    object actRight: TAction [4]
      Tag = 1
      Caption = 'actRight'
      ShortCut = 39
      OnExecute = actRightExecute
    end
  end
  object Timer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = TimerTimer
    Left = 28
    Top = 164
  end
  object dsrcState: TDataSource
    DataSet = mtState
    Left = 20
    Top = 88
  end
  object mtState: TMemTableEh
    Params = <>
    DataDriver = dsdState
    TreeList.KeyFieldName = 'ID'
    TreeList.RefParentFieldName = 'ID_P'
    TreeList.DefaultNodeExpanded = True
    TreeList.FilterNodeIfParentVisible = False
    AfterPost = mtStateAfterPost
    Left = 48
    Top = 88
  end
  object dsdState: TDataSetDriverEh
    ProviderDataSet = dsState
    Left = 76
    Top = 88
  end
  object dsState: TClientDataSet
    Aggregates = <>
    Params = <>
    Left = 104
    Top = 88
  end
  object dsrcDeposit: TDataSource
    DataSet = dsDeposit
    Left = 20
    Top = 448
  end
  object dsDeposit: TClientDataSet
    Aggregates = <>
    IndexFieldNames = 'ord_num'
    Params = <>
    AfterPost = dsCatalogAfterPost
    Left = 48
    Top = 448
  end
  object dsrcPerson: TDataSource
    DataSet = dsPerson
    Left = 20
    Top = 612
  end
  object dsPerson: TClientDataSet
    Aggregates = <>
    Params = <>
    AfterPost = dsCatalogAfterPost
    Left = 48
    Top = 612
  end
end
