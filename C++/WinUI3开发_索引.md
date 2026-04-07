
# XAML
```xml
<?xml version="1.0" encoding="utf-8"?>
<Window
    x:Class="PicViewer.MainWindow"
    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
    xmlns:local="using:PicViewer"
    xmlns:d="http://schemas.microsoft.com/expression/blend/2008"
    xmlns:mc="http://schemas.openxmlformats.org/markup-compatibility/2006"
    mc:Ignorable="d"
    Title="PicViewer">

    <Grid RequestedTheme="Default">
        <Grid.RowDefinitions>
            <RowDefinition Height="auto"/>
        </Grid.RowDefinitions>

        <MenuBar BorderBrush="Black" BorderThickness="1" CornerRadius="5">
            <MenuBarItem Title="File">

                <MenuFlyoutItem Text="Open" Click="Open_Click">
                    <MenuFlyoutItem.KeyboardAccelerators>
                        <KeyboardAccelerator Modifiers="Control" Key="O"/>
                    </MenuFlyoutItem.KeyboardAccelerators>
                </MenuFlyoutItem>

                <MenuFlyoutItem Text="Exit" Click="Exit_Click">
                    <MenuFlyoutItem.KeyboardAccelerators>
                        <KeyboardAccelerator Modifiers="Control" Key="E"/>
                    </MenuFlyoutItem.KeyboardAccelerators>
                </MenuFlyoutItem>
            </MenuBarItem>
        </MenuBar>
    </Grid>
</Window>
```
