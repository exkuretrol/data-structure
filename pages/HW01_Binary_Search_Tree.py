import random

import streamlit as st
from homework import BinarySearchTree

import redirect as rd
from menu import menu_with_redirect

menu_with_redirect()
st.header("二元搜尋樹")
st.caption("Binary Search Tree")

c1 = st.container(border=True)
c2 = st.container(border=True)
with c1:
    col1, col2 = st.columns([1, 1])
    with col1:
        input_options_action = {"create": "新增", "search": "搜尋"}

        input_action = st.radio(
            "action",
            input_options_action,
            format_func=lambda x: input_options_action.get(x),
            horizontal=True,
        )
    with col2:
        output_options = {
            "preorder": "前序",
            "inorder": "中序",
            "postorder": "後序",
        }

        output_method = st.radio(
            "output",
            output_options,
            format_func=lambda x: output_options.get(x),
            horizontal=True,
            index=1,
        )


with c2:
    if input_action == "create":
        input_options_method = {"manual": "手動設定", "random": "隨機產生"}

        input_method = st.radio(
            "method",
            input_options_method,
            format_func=lambda x: input_options_method.get(x),
            index=1,
            horizontal=True,
        )

        if input_method == "manual":
            input_num = st.number_input("num", min_value=0, max_value=2**31 - 1)

            st.sidebar.markdown(
                """
            `num`：輸入二元樹的數字。
            """
            )

        else:
            col1, col2 = st.columns([1, 3], gap="medium")
            with col1:
                input_n = st.number_input("n", min_value=1, max_value=100, value=3)
            with col2:
                input_minmax = st.slider(
                    "minmax", min_value=0, max_value=1000, value=(0, 100)
                )
            st.sidebar.markdown(
                """
            `n`：隨機輸入二元樹 n 個數字。

            `minmax`：輸入二元樹的數字的最大最小值。
            """
            )
    else:
        input_target = st.number_input("target", min_value=0, max_value=2**31 - 1)
    col1, col2, _, _ = st.columns([2, 2, 2, 5])
    with col1:
        btn_action = st.button(
            input_options_action.get(input_action),
            type="primary",
            use_container_width=True,
        )
    with col2:
        btn_empty = st.button(
            ":violet[清空 :bomb:]", type="secondary", use_container_width=True
        )


@st.cache_resource
def init_bst():
    return BinarySearchTree()


bst = init_bst()


def insert(num: int):
    bst.insert(num)
    st.toast(f"number {num} inserted!")


def search(num: int):
    result = bst.search(num)
    if result:
        st.info(f"number {num} founded.")
    else:
        st.error(f"number {num} not found!")


def empty():
    bst.empty()


if btn_action:
    if input_action == "create":
        if input_method == "manual":
            insert(input_num)
        else:
            m, M = input_minmax
            for _ in range(input_n):
                num = random.randint(m, M)
                insert(num)
    elif input_action == "search":
        search(input_target)

if btn_empty:
    empty()


code = st.code(language="css", body="", line_numbers=True)

if btn_action or output_method:
    with rd.stdout(to=code):
        if output_method == "preorder":
            bst.print(0)
        elif output_method == "inorder":
            bst.print(1)
        else:
            bst.print(2)
else:
    st.stop()
