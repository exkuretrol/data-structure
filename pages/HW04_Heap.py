import random
from typing import List

import streamlit as st
from homework import Heap

import redirect as rd
from menu import menu_with_redirect

menu_with_redirect()
st.header("堆積")
st.caption("Heap")

sidebar_text_list = list()
sidebar_text_list.append("---")

c0 = st.container(border=False)
c1 = st.container(border=True)

with c0:
    input_size = st.number_input("size", min_value=3, max_value=1000, value=100)

with c1:
    input_method_options = {"manual": "手動設定", "random": "隨機產生"}

    input_method = st.radio(
        "method",
        input_method_options,
        format_func=lambda x: input_method_options.get(x),
        index=1,
        horizontal=True,
    )

    if input_method == "manual":
        input_data = st.number_input("int", min_value=0, max_value=2**31 - 1)
        sidebar_text_list.append(f"`int`：輸入堆疊的數字。")

    else:
        col1, col2 = st.columns([1, 3], gap="medium")
        sidebar_text_list.append(f"`n`：隨機輸入堆疊 n 個數字。")
        with col1:
            input_n = st.number_input(
                "n", min_value=1, max_value=1000, value=input_size
            )
        with col2:
            input_minmax = st.slider(
                "minmax",
                min_value=0,
                max_value=1000,
                value=(0, 100),
            )

            sidebar_text_list.append(f"`mixmax`：輸入數字的最大最小值。")

col1, col2, col3, _ = st.columns([2, 2, 2, 5])
with col1:
    button_insert = st.button("新增", type="primary", use_container_width=True)
with col2:
    button_delete = st.button("刪除", use_container_width=True)
with col3:
    button_empty = st.button("清空 / 排序", use_container_width=True)


@st.cache_resource
def init_heap(size: int):
    return Heap(size)


heap = init_heap(input_size)


def insert(num: int):
    return heap.insert_heap(num)


def delete() -> int:
    return heap.delete_heap()


def get_n() -> int:
    return heap.get_n()


st.sidebar.markdown("\n\n".join(sidebar_text_list))


if button_insert:
    input_datas = []
    if input_method == "random":
        m, M = input_minmax
        for _ in range(input_n):
            num = random.randint(m, M)
            result = insert(num)
            if result == -1:
                st.error(f"堆疊已滿。無法再新增數字 {num}。")
                break
            input_datas.append(str(num))
        if len(input_datas) != 0:
            st.info(
                "新增了數字 %(num)s 到堆疊中" % {"num": ", ".join(input_datas)},
                icon="➕",
            )
    else:
        result = insert(input_data)
        if result == -1:
            st.error(f"堆疊已滿。無法再新增數字 {input_data}。")
        else:
            st.info(
                "新增了數字 %(num)i 到堆疊中" % {"num": input_data},
                icon="➕",
            )
if button_delete:
    num = delete()
    if num != -1:
        st.warning("堆疊頂端 %(num)i 已被刪除" % {"num": num}, icon="🗑️")
    else:
        st.error("堆疊已空")


def insert_all(nums: List[int]):
    for num in nums:
        insert(int(num))


if button_empty:
    heap_nums = list()
    n = get_n()
    if n == 0:
        st.error("堆疊已空")
    else:
        for i in range(n):
            num = delete()
            heap_nums.append(str(num))
        st.info(f"排序後的結果：{', '.join(heap_nums)}")

        col1, col2, _ = st.columns([4, 2, 6])
        col1.button(
            f"塞數字回堆疊！",
            on_click=insert_all,
            kwargs={"nums": heap_nums},
            type="primary",
            use_container_width=True,
        )
        col2.button("忽略", use_container_width=True)

code = st.code(language="css", body="", line_numbers=True)
with rd.stdout(to=code):
    heap.print()
