inherited fmReportStock: TfmReportStock
  Left = 818
  Top = 266
  Width = 1020
  Height = 414
  Caption = #1048#1079#1084#1077#1085#1077#1085#1080#1077' '#1086#1089#1090#1072#1090#1082#1086#1074' '#1085#1072' '#1089#1095#1077#1090#1072#1093
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited pnlFilter: TPanel
    Width = 1012
    inherited pnlDateIntervalType: TPanel
      inherited lDateIntervalType: TLabel
        OnClick = lDateIntervalTypeClick
      end
    end
  end
  inherited pnlMain: TPanel
    Width = 1012
    Height = 355
    object Splitter1: TSplitter
      Left = 273
      Top = 1
      Width = 4
      Height = 353
      Cursor = crHSplit
    end
    object dbgDeposit: TDBGridEh
      Tag = 2
      Left = 1
      Top = 1
      Width = 272
      Height = 353
      Align = alLeft
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
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      UseMultiTitle = True
      VertScrollBar.VisibleMode = sbNeverShowEh
      OnDrawColumnCell = dbgDepositDrawColumnCell
      OnGetCellParams = dbgDepositGetCellParams
      OnMouseUp = dbgDepositMouseUp
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
          Checkboxes = True
          EditButtons = <>
          FieldName = 'CHECKED'
          Footer.FieldName = 'CHECKED'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Caption = ' '
          Width = 27
        end
        item
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'COLOR'
          Footers = <>
          Title.Caption = #1062#1074#1077#1090
          Width = 30
        end>
      object RowDetailData: TRowDetailPanelControlEh
      end
    end
    object chrtMain: TChart
      Left = 277
      Top = 1
      Width = 734
      Height = 353
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
      Chart3DPercent = 25
      LeftAxis.AxisValuesFormat = '# ### ### ##0.00'
      LeftAxis.Grid.SmallDots = True
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
    end
  end
  inherited alMain: TActionList
    object actChangeDeposit: TAction [3]
      Caption = 'actChangeDeposit'
    end
  end
  object dsrcDeposit: TDataSource
    DataSet = dsDeposit
    Left = 24
    Top = 84
  end
  object dsDeposit: TClientDataSet
    Aggregates = <>
    IndexFieldNames = 'ord_num'
    Params = <>
    AfterPost = dsCatalogAfterPost
    Left = 52
    Top = 84
  end
  object Timer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = TimerTimer
    Left = 28
    Top = 164
  end
end
