inherited fmReportTurnoverDynamic: TfmReportTurnoverDynamic
  Left = 713
  Top = 254
  Caption = #1044#1080#1085#1072#1084#1080#1082#1072' '#1076#1074#1080#1078#1077#1085#1080#1103' '#1089#1088#1077#1076#1089#1090#1074
  PixelsPerInch = 96
  TextHeight = 13
  inherited pnlFilter: TPanel
    inherited pnlDateIntervalType: TPanel
      inherited lDateIntervalType: TLabel
        OnClick = lDateIntervalTypeClick
      end
    end
  end
  inherited pnlMain: TPanel
    inherited pnlOpts: TPanel
      inherited dbgPerson: TDBGridEh
        Columns = <
          item
            EditButtons = <>
            FieldName = 'NAME'
            Footer.FieldName = 'NAME'
            Footer.ValueType = fvtCount
            Footers = <>
            ReadOnly = True
            Title.Caption = #1053#1072#1079#1085#1072#1095#1077#1085#1080#1077
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
            Width = 26
          end>
      end
    end
    inherited pnlRes: TPanel
      object Splitter1: TSplitter
        Left = 0
        Top = 281
        Width = 515
        Height = 3
        Cursor = crVSplit
        Align = alBottom
      end
      object pnlData: TPanel
        Left = 0
        Top = 284
        Width = 515
        Height = 490
        Align = alBottom
        BevelOuter = bvNone
        TabOrder = 0
        object dbgData: TDBGridEh
          Tag = 2
          Left = 0
          Top = 0
          Width = 515
          Height = 490
          Align = alClient
          AllowedOperations = []
          AutoFitColWidths = True
          ColumnDefValues.Title.Alignment = taCenter
          Ctl3D = False
          DataGrouping.GroupLevels = <>
          DataSource = dsrcData
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
          RowDetailPanel.Active = True
          RowDetailPanel.Height = 280
          RowDetailPanel.ActiveControl = dbgDoc
          RowDetailPanel.BevelInner = bvNone
          RowDetailPanel.BevelOuter = bvNone
          RowDetailPanel.BorderStyle = bsNone
          SumList.Active = True
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'MS Sans Serif'
          TitleFont.Style = []
          OnRowDetailPanelShow = dbgDataRowDetailPanelShow
          Columns = <
            item
              DisplayFormat = 'dd.MM.yyyy'
              EditButtons = <>
              FieldName = 'INTERVAL_FROM'
              Footer.FieldName = 'INTERVAL_FROM'
              Footer.ValueType = fvtCount
              Footers = <>
              Title.Caption = #1057
              Width = 99
            end
            item
              DisplayFormat = 'dd.MM.yyyy'
              EditButtons = <>
              FieldName = 'INTERVAL_TO'
              Footers = <>
              Title.Caption = #1055#1086
              Width = 156
            end
            item
              DisplayFormat = '# ### ### ##0.00'
              EditButtons = <>
              FieldName = 'SUMMA'
              Footer.DisplayFormat = '# ### ### ##0.00'
              Footer.FieldName = 'SUMMA'
              Footer.ValueType = fvtSum
              Footers = <>
              Title.Caption = #1057#1091#1084#1084#1072
              Width = 187
            end>
          object RowDetailData: TRowDetailPanelControlEh
            object dbgDoc: TDBGridEh
              Tag = 2
              Left = 0
              Top = 0
              Width = 426
              Height = 280
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
              FooterFont.Height = -11
              FooterFont.Name = 'MS Sans Serif'
              FooterFont.Style = []
              FooterRowCount = 1
              IndicatorOptions = [gioShowRowIndicatorEh]
              OddRowColor = 15790320
              Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
              ParentCtl3D = False
              ReadOnly = True
              RowDetailPanel.Active = True
              RowDetailPanel.Height = 200
              RowDetailPanel.ActiveControl = dbgStr
              RowDetailPanel.BevelInner = bvNone
              RowDetailPanel.BevelOuter = bvNone
              RowDetailPanel.BorderStyle = bsNone
              SumList.Active = True
              TabOrder = 0
              TitleFont.Charset = DEFAULT_CHARSET
              TitleFont.Color = clWindowText
              TitleFont.Height = -11
              TitleFont.Name = 'MS Sans Serif'
              TitleFont.Style = []
              OnRowDetailPanelShow = dbgDocRowDetailPanelShow
              Columns = <
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
                  Tag = 2
                  Left = 0
                  Top = 0
                  Width = 393
                  Height = 200
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
                  FooterFont.Height = -11
                  FooterFont.Name = 'MS Sans Serif'
                  FooterFont.Style = []
                  FooterRowCount = 1
                  IndicatorOptions = [gioShowRowIndicatorEh]
                  OddRowColor = 15790320
                  Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
                  ParentCtl3D = False
                  RowDetailPanel.Height = 100
                  SumList.Active = True
                  TabOrder = 0
                  TitleFont.Charset = DEFAULT_CHARSET
                  TitleFont.Color = clWindowText
                  TitleFont.Height = -11
                  TitleFont.Name = 'MS Sans Serif'
                  TitleFont.Style = []
                  VertScrollBar.VisibleMode = sbNeverShowEh
                  OnGetCellParams = dbgStrGetCellParams
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
      end
      object chrtMain: TChart
        Left = 0
        Top = 0
        Width = 515
        Height = 281
        AnimatedZoom = True
        AnimatedZoomSteps = 4
        BackWall.Brush.Color = clWhite
        MarginBottom = 0
        MarginLeft = 0
        MarginRight = 0
        MarginTop = 0
        Title.Text.Strings = (
          'TChart')
        Title.Visible = False
        OnClickSeries = chrtMainClickSeries
        Chart3DPercent = 25
        LeftAxis.AxisValuesFormat = '# ### ### ##0.00'
        LeftAxis.Grid.SmallDots = True
        LeftAxis.Inverted = True
        LeftAxis.Ticks.Width = 2
        LeftAxis.TicksInner.Visible = False
        Legend.Visible = False
        View3D = False
        View3DOptions.Elevation = 315
        View3DOptions.Orthogonal = False
        View3DOptions.Perspective = 0
        View3DOptions.Rotation = 360
        View3DWalls = False
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 1
        AutoSize = True
        object Ser: TBarSeries
          ColorEachPoint = True
          Marks.ArrowLength = 20
          Marks.Style = smsValue
          Marks.Visible = True
          SeriesColor = clRed
          ShowInLegend = False
          Title = 'Ser'
          BarStyle = bsRectGradient
          XValues.DateTime = True
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Bar'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object NullLine: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clBlack
          ShowInLegend = False
          Dark3D = False
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.DateTime = True
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
      end
    end
  end
  object dsrcData: TDataSource
    DataSet = dsData
    Left = 280
    Top = 500
  end
  object dsData: TClientDataSet
    Aggregates = <>
    FieldDefs = <>
    IndexDefs = <
      item
        Name = 'dsDataIndex'
        DescFields = 'ord_num'
        Fields = 'ord_num'
        Options = [ixDescending]
      end>
    IndexName = 'dsDataIndex'
    Params = <>
    StoreDefs = True
    Left = 308
    Top = 500
  end
  object dsrcDoc: TDataSource
    DataSet = dsDoc
    Left = 280
    Top = 528
  end
  object dsDoc: TClientDataSet
    Aggregates = <>
    Params = <>
    Left = 308
    Top = 528
  end
  object dsrcStr: TDataSource
    DataSet = dsStr
    Left = 280
    Top = 556
  end
  object dsStr: TClientDataSet
    Aggregates = <>
    Params = <>
    Left = 308
    Top = 556
  end
end
