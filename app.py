import streamlit as st

from menu import menu

st.set_page_config(page_title="08170875 資工作業", page_icon="😾")

st.write(
    """
# 作業存放區
"""
)

st.caption("08170875 陳家瑋")

st.info("選擇課程後，點選一個作業顯示。")


menu()

st.markdown(
    """[![GitHub last commit](https://img.shields.io/github/last-commit/exkuretrol/data-structure?display_timestamp=author&style=flat&logo=github&link=https%3A%2F%2Fgithub.com%2Fexkuretrol%2Fdata-structure)](https://github.com/exkuretrol/data-structure)
    """
)

st.page_link(page="https://kuaz.info", label="卍煞氣a饅頭卍", icon="😾")
